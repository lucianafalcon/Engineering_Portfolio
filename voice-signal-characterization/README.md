# Voice Signal Analysis / Análisis de la Señal de Voz

This repository contains a signal processing project focused on the spectral and temporal analysis of the human voice, as well as voice modification techniques such as pitch shifting and time stretching, implemented in Python.

## Summary

This project explores various techniques for analyzing and transforming speech signals. It includes:
Spectral analysis using the Fourier Transform (FFT),
short-Time Fourier Transform (STFT) for spectrograms,
time-domain and frequency-domain pitch and speed modifications,
TD-PSOLA and Phase Vocoder techniques, and
the results demonstrate the value of spectral-temporal processing for speech transformation, pitch shifting, and intelligibility preservation in different use cases.

## Requirements

- Python 3.x  
- Dependencies: `numpy`, `scipy`, `matplotlib`, `sounddevice`, `librosa`

Install dependencies with:

```bash
pip install numpy scipy matplotlib sounddevice librosa
```

## How to Run
Optional: record your own voice

```bash
python 0_grabacion_voz.py
```

Run the analysis scripts

For example:
```bash
python 1_fft_completa_mejorada.py
python 2_TD-PSOLA.py
python 3_TFCT_disminucion_velocidad_señal_rapida_mejorada.py
```
Output .wav files will be saved in the same directory.


## Report

The full project report is available here:

 [technical report](./technical_report_en.pdf )

---

⬇️ Scroll down for the full README in Spanish.

<details>
 <summary>Este repositorio contiene un proyecto de procesamiento de señales enfocado en el análisis espectral y temporal de la voz humana, así como en técnicas de modificación vocal, como el cambio de pitch y la variación de velocidad, implementadas en Python. </summary>

## Resumen

Este proyecto explora diversas técnicas para analizar y transformar señales de voz. Incluye:
Análisis espectral mediante la Transformada de Fourier (FFT),
transformada de Fourier de Tiempo Corto (STFT) para espectrogramas,
modificaciones de tono y velocidad en dominio temporal y frecuencia,
técnicas TD-PSOLA y vocoder de fase, y
los resultados demuestran la utilidad del procesamiento espectral-temporal para la transformación de la voz, cambio de pitch y preservación de la inteligibilidad en distintas aplicaciones.
  
## ⚙️ Requisitos

Python 3.x

Dependencias: numpy, scipy, matplotlib, sounddevice, librosa

Instala las dependencias con:

```bash
pip install numpy scipy matplotlib sounddevice librosa
```

## Cómo Ejecutar

Opcional: grabar tu propia voz

```bash
python 0_grabacion_voz.py
```
Ejecutar los scripts de análisis

Por ejemplo:

```bash
python 1_fft_completa_mejorada.py
python 2_TD-PSOLA.py
python 3_TFCT_disminucion_velocidad_señal_rapida_mejorada.py 
```
Los archivos .wav de salida se guardarán en el mismo directorio.

## Informe

El informe completo del proyecto disponible en:

 [informe técnico](./informe_tecnico_es.pdf) 

</details>
