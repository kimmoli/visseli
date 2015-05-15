/*
    visseli, Visseli
*/

#include "morse.h"

Morse::Morse(QObject *parent) :
    QObject(parent),
    _audio_resource(this, AudioResourceQt::AudioResource::MediaType)
{
    emit versionChanged();

    _initialised = false;
    emit initialisedChanged();

    _vuValue = 0;
    emit vuValueChanged();

    QObject::connect(&_audio_resource, SIGNAL(acquiredChanged()),
                     this, SLOT(audioAcquire()));
}

Morse::~Morse()
{
}

QString Morse::readVersion()
{
    return APPVERSION;
}

void Morse::init()
{
    if (!_initialised)
    {
        mmar = new QMultimediaAudioRecorder();

        connect(mmar, SIGNAL(vuMeterValueUpdate(float)), this, SLOT(vuMeterValueUpdate(float)));

        _initialised = true;
        emit initialisedChanged();
    }
}

void Morse::rec()
{
    if (_initialised)
        mmar->startRecord("/tmp/visseli.wav");
}

void Morse::stop()
{
    if (_initialised)
        mmar->stopRecord();
}

void Morse::vuMeterValueUpdate(float value)
{
    if (value > 0.01 && _vuValue == 0)
    {
        _vuValue = 1;
        emit vuValueChanged();
    }
    else if (value < 0.01 && _vuValue == 1)
    {
        _vuValue = 0;
        emit vuValueChanged();
    }

}

void Morse::beep()
{
    _audio_resource.acquire();
}

void Morse::audioAcquire()
{

     if (!_audio_resource.isAcquired())
         return;

    _format.setSampleRate(44100);
    _format.setChannelCount(1);
    _format.setSampleSize(16);
    _format.setCodec("audio/pcm");
    _format.setByteOrder(QAudioFormat::LittleEndian);
    _format.setSampleType(QAudioFormat::SignedInt);

    if (!gen)
    {
        delete gen;
        gen = 0;
    }

    gen = new Generator(_format, 1000000, 600, this);

    if (!_audioOutput)
    {
        delete _audioOutput;
        _audioOutput = 0;
    }

    _audioOutput = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), _format, this);
    gen->start();

    _audioOutput->start(gen);
}
