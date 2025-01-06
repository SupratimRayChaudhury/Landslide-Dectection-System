# Landslide Detection System

Welcome to the Landslide Detection System repository
## Introduction
This project aims to develop a cost-effective landslide detection system. Initially, we focus on integrating various sensors using Arduino or Raspberry Pi boards. These sensors include:
- Moisture sensor
- 3D accelerometer
- Rain gauge
- Temperature sensor
- Humidity sensor
- Tilt sensor

We provide the code for interfacing and collecting data from each of these sensors.

## Sensor Codes
- `moisture_sensor_code.ino`
- `accelerometer_code.ino`
- `rain_gauge_code.ino`
- `temperature_sensor_code.ino`
- `humidity_sensor_code.ino`
- `tilt_sensor_code.ino`

Feel free to explore and utilize these codes for your own projects!

## Second Stage
The second stage of our project involves data analysis using machine learning modules.
## Data Description

The Landslideslide dataset has three splits, training/validation/test, consisting of 3799, 245, and 800 image patches, respectively. Each image patch is a composite of 14 bands that include:

- **Multispectral data** from [Sentinel-2](https://sentinel.esa.int/web/sentinel/missions/sentinel-2): B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12.

- **Slope data** from [ALOS PALSAR](https://www.usgs.gov/centers/eros/science/usgs-eros-archive-radar-alos-palsar-radar-processing-system): B13.

- **Digital elevation model (DEM)** from [ALOS PALSAR](https://www.usgs.gov/centers/eros/science/usgs-eros-archive-radar-alos-palsar-radar-processing-system): B14.

All bands in the competition dataset are resized to the resolution of ~10m per pixel. The image patches have the size of 128 x 128 pixels and are labeled pixel-wise.

**Download links:** [training](https://cloud.iarai.ac.at/index.php/s/KrwKngeXN7KjkFm) and [validation](https://cloud.iarai.ac.at/index.php/s/N6TacGsfr5nRNWr).

![Logo](/image/Data_figure.png?raw=true "landslide_detection")

The _Landslide4Sense_ dataset is structured as follows:

```
├── TrainData/
│   ├── img/
|   |   ├── image_1.h5
|   |   ├── ...
|   |   ├── image_3799.h5
│   ├── mask/
|   |   ├── mask_1.h5
|   |   ├── ...
|   |   ├── mask_3799.h5
├── ValidData/
|   ├── img/
|   |   ├── image_1.h5
|   |   ├── ...
|   |   ├── image_245.h5
├── TestData/
    ├── img/
        ├── image_1.h5
        ├── ...
        ├── image_800.h5
```

Note that the label files (mask files) are only accessible in the training set.

Mapping classes used in the competition:

| Class Number |  Class Name   | Class Code in the Label |
| :----------: | :-----------: | :---------------------: |
|      1       | Non-landslide |            0            |
|      2       |   Landslide   |            1            |
