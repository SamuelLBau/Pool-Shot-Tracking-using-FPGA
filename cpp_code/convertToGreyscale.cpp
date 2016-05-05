#include <hls_video.h>
#define MAX_WIDTH 2047
#define MAX_HEIGHT 2047

typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3> hlsMat;

void convertToGreyScale(hlsMat *originalFrame, hlsMat *convertedFrame) {
	hls::CvtColor<HLS_RGB2GRAY>(*originalFrame, *convertedFrame);
}

