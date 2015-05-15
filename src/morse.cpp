/*
    visseli, Visseli
*/

#include "morse.h"
 #include <QAudioDeviceInfo>

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
                     this, SLOT(audioAcquired()));

    _playing = false;
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
    if (!_playing)
    {
        qDebug() << "acquiring audioresource";
        _audio_resource.acquire();
    }
    else
    {
        qDebug() << "releasing audioresource";
        _audio_resource.release();

        qDebug() << "stopping";
        _audioOutput->stop();
        gen->stop();
        delete _audioOutput;
        _audioOutput = 0;
        delete gen;
        gen = 0;

        _playing = false;
    }
}

void Morse::audioAcquired()
{
    qDebug() << "audioAcquiredChanged" << _audio_resource.isAcquired();

    if (_audio_resource.isAcquired() && !_playing)
    {
        qDebug() << "playing";

        _format.setSampleRate(44100);
        _format.setChannelCount(1);
        _format.setSampleSize(16);
        _format.setCodec("audio/pcm");
        _format.setByteOrder(QAudioFormat::LittleEndian);
        _format.setSampleType(QAudioFormat::SignedInt);

        if (QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).isEmpty())
        {
            qWarning() << "no audio output devices";
            return;
        }

        if (!QAudioDeviceInfo::defaultOutputDevice().isFormatSupported(_format))
        {
            qWarning() << "raw audio format not supported by backend, cannot play audio.";
            return;
        }

        if (!gen)
        {
            delete gen;
            gen = 0;
        }

        gen = new Generator(_format, 1000, 600, this);

        if (!_audioOutput)
        {
            delete _audioOutput;
            _audioOutput = 0;
        }

        _audioOutput = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), _format, this);
        gen->start();

        _audioOutput->start(gen);

        _playing = true;
    }
}
