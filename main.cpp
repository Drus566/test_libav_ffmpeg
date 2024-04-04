/** Вывод информации о
 * кодеке, 
 * контейнере, 
 * ширине/высоте, 
 * количестве кадров, 
 * так же информацию об аудио дорожке
*/

/** Компиляция
 * g++ test.cpp -o test -lavformat -lavcodec -lavutil
*/

#include <iostream>
extern "C" 
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        av_log(NULL, AV_LOG_ERROR, "Usage: <input file>\n");
        return -1;
    }
    const char* input_file = argv[1];

    AVFormatContext *ctx = avformat_alloc_context();

    if (avformat_open_input(&ctx, input_file, NULL, NULL) != 0) return -1;
    if (avformat_find_stream_info(ctx, NULL) < 0) return -1;
    
    // Выводим информацию о кодеке
    for (int i = 0; i < ctx->nb_streams; i++) {
        AVCodecParameters *codec_params = ctx->streams[i]->codecpar;
        const AVCodec *codec = avcodec_find_decoder(codec_params->codec_id);
        if (codec) { 
            std::cout << "\nCodec information - " << codec->name << ":" << std::endl;
            std::cout << "Long name: " << codec->long_name << std::endl;
            std::cout << "Unique identificator: " << codec->id << std::endl;
            std::cout << "Type (1 - Audio or 0 - Video): " << codec->type << std::endl;
        }
    }

    // Выводим информацию о контейнере
    std::cout << "\nContainer information:" << std::endl;
    std::cout << "Format name: " << ctx->iformat->name << std::endl;
    std::cout << "Format long name: " << ctx->iformat->long_name << std::endl;
    std::cout << "Duration: " << ctx->duration / AV_TIME_BASE << " seconds" << std::endl;
    std::cout << "Bit rate: " << ctx->bit_rate / 1000 << " kbps" << std::endl;
    
    // Выводим информацию о ширине и высоте
    for (int i = 0; i < ctx->nb_streams; i++) {
        if (ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            std::cout << "\nWidth: " << ctx->streams[i]->codecpar->width << std::endl;
            std::cout << "Height: " << ctx->streams[i]->codecpar->height << std::endl;
        }
    }

    // Выводим информацию о количестве кадров
    int64_t total_frames = 0;
    for (int i = 0; i < ctx->nb_streams; i++) {
        if (ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            AVStream *stream = ctx->streams[i];
            total_frames += stream->nb_frames;
            break;
        }
    }
    std::cout << "\nTotal number of frames: " << total_frames << std::endl;

    // Выводим информацию о аудио дорожке
    for (int i = 0; i < ctx->nb_streams; i++) {
        if (ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            std::cout << "\nAudio stream information:" << std::endl;
            // std::cout << "Codec name: " << ctx->streams[i]->codecpar->codec_name << std::endl;
            const AVCodec *codec = avcodec_find_decoder(ctx->streams[i]->codecpar->codec_id);
            if (codec) {
                std::cout << "Codec name: " << codec->name << std::endl;
            }
            std::cout << "Sample rate: " << ctx->streams[i]->codecpar->sample_rate << std::endl;
            std::cout << "Channels: " << ctx->streams[i]->codecpar->ch_layout.nb_channels << std::endl;
            break;
        }
    }

    if (ctx != NULL) {
        avformat_close_input(&ctx);
        avformat_free_context(ctx);
    }

    return 0;
}
