/**
 * @copyright (C) 2017 Melexis N.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef _mlx90640_API_H_
#define _mlx90640_API_H_

#include <QObject>
#include <QStringList>
#include <QVector>
#include <array>

#define mlx90640_DEV_ADDR 0x33

#define mlx90640_NO_ERROR 0
#define mlx90640_I2C_NACK_ERROR 1
#define mlx90640_I2C_WRITE_ERROR 2
#define mlx90640_BROKEN_PIXELS_NUM_ERROR 3
#define mlx90640_OUTLIER_PIXELS_NUM_ERROR 4
#define mlx90640_BAD_PIXELS_NUM_ERROR 5
#define mlx90640_ADJACENT_BAD_PIXELS_ERROR 6
#define mlx90640_EEPROM_DATA_ERROR 7
#define mlx90640_FRAME_DATA_ERROR 8
#define mlx90640_MEAS_TRIGGER_ERROR 9

#define BIT_MASK(x) (1UL << (x))
#define REG_MASK(sbit,nbits) ~((~(~0UL << (nbits))) << (sbit))

#define mlx90640_EEPROM_START_ADDRESS 0x2400
#define mlx90640_EEPROM_DUMP_NUM 832
#define mlx90640_PIXEL_DATA_START_ADDRESS 0x0400
#define mlx90640_PIXEL_NUM 768
#define mlx90640_LINE_NUM 24
#define mlx90640_COLUMN_NUM 32
#define mlx90640_LINE_SIZE 32
#define mlx90640_COLUMN_SIZE 24
#define mlx90640_AUX_DATA_START_ADDRESS 0x0700
#define mlx90640_AUX_NUM 64
#define mlx90640_STATUS_REG 0x8000
#define mlx90640_INIT_STATUS_VALUE 0x0030
#define mlx90640_STAT_FRAME_MASK BIT_MASK(0)
#define mlx90640_GET_FRAME(reg_value) (reg_value & mlx90640_STAT_FRAME_MASK)
#define mlx90640_STAT_DATA_READY_MASK BIT_MASK(3)
#define mlx90640_GET_DATA_READY(reg_value) (reg_value & mlx90640_STAT_DATA_READY_MASK)

#define mlx90640_CTRL_REG 0x800D
#define mlx90640_CTRL_TRIG_READY_MASK BIT_MASK(15)
#define mlx90640_CTRL_REFRESH_SHIFT 7
#define mlx90640_CTRL_REFRESH_MASK REG_MASK(mlx90640_CTRL_REFRESH_SHIFT,3)
#define mlx90640_CTRL_RESOLUTION_SHIFT 10
#define mlx90640_CTRL_RESOLUTION_MASK REG_MASK(mlx90640_CTRL_RESOLUTION_SHIFT,2)
#define mlx90640_CTRL_MEAS_MODE_SHIFT 12
#define mlx90640_CTRL_MEAS_MODE_MASK BIT_MASK(12)

#define mlx90640_MS_BYTE_SHIFT 8
#define mlx90640_MS_BYTE_MASK 0xFF00
#define mlx90640_LS_BYTE_MASK 0x00FF
#define mlx90640_MS_BYTE(reg16) ((reg16 & mlx90640_MS_BYTE_MASK) >> mlx90640_MS_BYTE_SHIFT)
#define mlx90640_LS_BYTE(reg16) (reg16 & mlx90640_LS_BYTE_MASK)
#define mlx90640_MSBITS_6_MASK 0xFC00
#define mlx90640_LSBITS_10_MASK 0x03FF
#define mlx90640_NIBBLE1_MASK 0x000F
#define mlx90640_NIBBLE2_MASK 0x00F0
#define mlx90640_NIBBLE3_MASK 0x0F00
#define mlx90640_NIBBLE4_MASK 0xF000
#define mlx90640_NIBBLE1(reg16) ((reg16 & mlx90640_NIBBLE1_MASK))
#define mlx90640_NIBBLE2(reg16) ((reg16 & mlx90640_NIBBLE2_MASK) >> 4)
#define mlx90640_NIBBLE3(reg16) ((reg16 & mlx90640_NIBBLE3_MASK) >> 8)
#define mlx90640_NIBBLE4(reg16) ((reg16 & mlx90640_NIBBLE4_MASK) >> 12)

#define POW2(x) pow(2, (double)x)

#define SCALEALPHA 0.000001

#include <stdint.h>

class MLX90640 : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(bool initialized READ getInitialized WRITE setInitialized NOTIFY initializedChanged)
    Q_PROPERTY(QVector<float> imageVect READ getImageVect NOTIFY dataReady)

    QVector<float> getImageVect() const {
        return this->imageVect;
    }

    bool initialized = false;

    bool getInitialized() {
        return this->initialized;
    }

    void setInitialized(bool val) {
        if (this->initialized != val) {
            this->initialized = val;
            emit initializedChanged();
        }
    }

    typedef struct
        {
            int16_t kVdd;
            int16_t vdd25;
            float KvPTAT;
            float KtPTAT;
            uint16_t vPTAT25;
            float alphaPTAT;
            int16_t gainEE;
            float tgc;
            float cpKv;
            float cpKta;
            uint8_t resolutionEE;
            uint8_t calibrationModeEE;
            float KsTa;
            float ksTo[5];
            int16_t ct[5];
            uint16_t alpha[768];
            uint8_t alphaScale;
            int16_t offset[768];
            int8_t kta[768];
            uint8_t ktaScale;
            int8_t kv[768];
            uint8_t kvScale;
            float cpAlpha[2];
            int16_t cpOffset[2];
            float ilChessC[3];
            uint16_t brokenPixels[5];
            uint16_t outlierPixels[5];
        } paramsMLX90640;

    unsigned char slaveAddress = 0x33;
    paramsMLX90640 mlx90640;

    int mlx90640_DumpEE(uint8_t slaveAddr, uint16_t *eeData);
    int mlx90640_SynchFrame(uint8_t slaveAddr);
    int mlx90640_TriggerMeasurement(uint8_t slaveAddr);
    Q_INVOKABLE int mlx90640_GetFrameData(uint8_t slaveAddr, uint16_t *frameData);
    int mlx90640_ExtractParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    Q_INVOKABLE float mlx90640_GetVdd(uint16_t *frameData, const paramsMLX90640 *params);
    Q_INVOKABLE float mlx90640_GetTa(uint16_t *frameData, const paramsMLX90640 *params);
    Q_INVOKABLE void mlx90640_GetImage(uint16_t *frameData, const paramsMLX90640 *params, float *result);
    void mlx90640_CalculateTo(uint16_t *frameData, const paramsMLX90640 *params, float emissivity, float tr, float *result);
    Q_INVOKABLE int mlx90640_SetResolution(uint8_t slaveAddr, uint8_t resolution);
    int mlx90640_GetCurResolution(uint8_t slaveAddr);
    Q_INVOKABLE int mlx90640_SetRefreshRate(uint8_t slaveAddr, uint8_t refreshRate);
    int mlx90640_GetRefreshRate(uint8_t slaveAddr);
    int mlx90640_GetSubPageNumber(uint16_t *frameData);
    int mlx90640_GetCurMode(uint8_t slaveAddr);
    Q_INVOKABLE int mlx90640_SetInterleavedMode(uint8_t slaveAddr);
    Q_INVOKABLE int mlx90640_SetChessMode(uint8_t slaveAddr);
    void mlx90640_BadPixelsCorrection(uint16_t *pixels, float *to, int mode, paramsMLX90640 *params);

    Q_INVOKABLE void fuzzyInit(){
        int status;
        status = mlx90640_SetRefreshRate (0x33,0x05);   //16hz
        status = mlx90640_SetResolution(0x33,0x00);     //16 bit res
        status = mlx90640_SetChessMode (0x33);          //chess interlacing mode
        getData();                                      //test read(initial)

        // Print out the array
        for (int i = 0; i < imageVect.size(); ++i) {
            fprintf(stderr, "ImageVect[%d]: %f\n", i, imageVect[i]);
        }

        emit initializedChanged();
    }

    Q_INVOKABLE void getData(){
        uint16_t eeMLX90640[832];
        uint16_t mlx90640Frame[834];
        float mlx90640Image[768];
        int status;

        status = mlx90640_DumpEE (slaveAddress, eeMLX90640);
        status = mlx90640_ExtractParameters(eeMLX90640, &mlx90640);
        status = mlx90640_GetFrameData (0x33, mlx90640Frame);
        mlx90640_GetImage(mlx90640Frame, &mlx90640, mlx90640Image);

        for (int i = 0; i < 767; ++i) {
            imageVect[i] = mlx90640Image[i];
        }

        emit dataReady();
    }

    MLX90640() : imageVect(768){}

    QVector<float> imageVect;
protected:
    void ExtractVDDParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractPTATParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractGainParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractTgcParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractResolutionParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractKsTaParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractKsToParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractAlphaParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractOffsetParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractKtaPixelParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractKvPixelParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractCPParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    void ExtractCILCParameters(uint16_t *eeData, paramsMLX90640 *MLX90640);
    int ExtractDeviatingPixels(uint16_t *eeData, paramsMLX90640 *MLX90640);
    int CheckAdjacentPixels(uint16_t pix1, uint16_t pix2);
    float GetMedian(float *values, int n);
    int IsPixelBad(uint16_t pixel,paramsMLX90640 *params);
    int ValidateFrameData(uint16_t *frameData);
    int ValidateAuxData(uint16_t *auxData);
signals:
    void dataReady();
    void initializedChanged();
};
#endif
