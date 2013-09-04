
#include "fbx_unzip.hpp"

extern "C" {
	#include <string.h>
	#include <zlib.h>
}

namespace FBX {
	std::vector<uint8_t> inflate(const std::vector<uint8_t> &data, size_t out_hint) {
		z_stream strm;
		int ret;
		memset(&strm, 0, sizeof(strm));
		uint8_t out[4096];
		std::vector<uint8_t> result;

		result.reserve(out_hint);

		ret = ::inflateInit(&strm);
		if (ret != Z_OK) throw InflateException("inflateInit failed");

		strm.avail_in = (unsigned int) data.size();
		strm.next_in = const_cast<unsigned char*>(data.data());

		strm.avail_out = sizeof(out);
		strm.next_out = out;

		for (;;) {
			ret = ::inflate(&strm, Z_FINISH);
			if (ret != Z_OK && ret != Z_BUF_ERROR) break;

			if (strm.next_out == out) {
				inflateEnd(&strm);
				throw InflateException("inflate: no progress");
			}

			result.insert(result.end(), out, strm.next_out);

			strm.avail_out = sizeof(out);
			strm.next_out = out;
		}
		result.insert(result.end(), out, strm.next_out);

		::inflateEnd(&strm);

		switch (ret) {
		case Z_STREAM_END:
			break;
		case Z_STREAM_ERROR:
			throw InflateException("inflate: stream error");
		case Z_NEED_DICT:
			throw InflateException("inflate: need dict");
		case Z_DATA_ERROR:
			throw InflateException("inflate: data error");
		case Z_MEM_ERROR:
			throw InflateException("inflate: memory error");
		default:
			throw InflateException("inflate: unknown error");
		}

		return result;
	}
}
