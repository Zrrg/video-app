#include <inttypes.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

bool load_frame(const char* filename, int* width, int* height, unsigned char** data) {

    /* Open the file using libavformat */
    AVFormatContext* av_format_ctx = avformat_alloc_context();
    if (!av_format_ctx) {
        printf("Couldn't create AVFormatContext\n");
        return false;
    }
    
    if (avformat_open_input(&av_format_ctx, filename, NULL, NULL) != 0) {
        printf("Couldn't open video file\n");
        return false;
    }

    /* Find the first valid video stream inside the file */
    int video_stream_index = -1;
    int audio_stream_index = -1;
    AVCodecParameters* av_codec_params;
    const AVCodec* av_codec;

    for (int i = 0; i < av_format_ctx->nb_streams; ++i) {
        auto stream = av_format_ctx->streams[i];
        av_codec_params = av_format_ctx->streams[i]->codecpar;
        av_codec = avcodec_find_decoder(av_codec_params->codec_id);

        if (!av_codec) {
            continue;
        }
        if (av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index = i;
            break;
        }                    
    }

    if (video_stream_index == -1) {
        printf("Couldn't find valid video stream inside file\n");
        return false;
    }

    /* Set up a codec context for the decoder */
    AVCodecContext* av_codec_ctx = avcodec_alloc_context3(av_codec);
    if (!av_codec_ctx) {
        printf("Couldn't create AVCodecContext\n");
        return false;
    }

    if (!avcodec_parameters_to_context(av_codec_ctx, av_codec_params)) {
        printf("Couldn't initialize AVCodecContext\n");
    }

    if (!avcodec_open2(av_codec_ctx, av_codec, NULL) < 0) {
        printf("Couldn't open codec\n");
        return false;
    }


    AVFrame* av_frame = av_frame_alloc();
    if (!av_frame) {
        printf("Couldn't allocate AVFrame\n");
        return false;
    }
    AVPacket* av_packet = av_packet_alloc();
    if (!av_packet) {
        printf("Couldn't allocate AVPacket\n");
        return false;
    }

    avformat_close_input(&av_format_ctx);
    avformat_free_context(av_format_ctx);
    avcodec_free_context(&av_codec_ctx);

    return true;
}
