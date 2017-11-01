/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    RtvContext.h
 * @brief
 *******************************************************************************
 */
#ifndef RTVCONTEXT_H
#define RTVCONTEXT_H

#include <QByteArray>
#include <QImage>
#include <QVector>

#include "image_buffer/ImageBuffer.h"
#include "image_buffer/RtvImageLoader.h"

struct Head
{
    QByteArray magic_code;
    char flags : 1;
    QByteArray version;
    QByteArray device_id;
    qint64 start_time;
    int start_position[3];
    uint frames_count;
    uint frame_max;
    uint video_resolution[2];
    char frame_format;
    char frame_codec;
    uint tagging_flags;
};

struct TagStruct
{
    uint time_flag;           // 0 4
    qint64 data_offset;       // 4 8
    uint data_length;         // 12 4
    int relative_position[3]; // 16 4,4,4
    uint relative_distance;   // 28 4
    short speed;              // 32 2
    short direction;          // 34 2
    // version 0.4
    short can_data_length; // 36 2
    uint acceleration_x;   // 38 2
    uint acceleration_y;
    uint acceleration_z;
    uint pitch_rate;
    uint roll_rate;
    uint yaw_rate;
    uint longitudinal_gradient_roadway;
    uint traverse_gradient_roadway;
    short travelled_distance;
    uchar is_reverse_gear;              // 1
    uint slip_angle;                    // 4
    uint front_wheel_steering_angle;    // 77 4
    uint rear_wheel_wteering_angle;     // 81 4
    uint steering_wheel_steering_angle; // 85 4
    uint vehicle_speed;                 // 89 4
    uint wheel_tick_left_front;         // 93 4
    uint wheel_tick_right_front;        // 97 4
    uint wheel_tick_left_rear;          // 101 4
    uint wheel_tick_right_rear;         // 105 4

    uint wheel_speed_left_front;     // 109 4
    uint wheel_speed_right_front;    // 113 4
    uint wheel_speed_left_rear;      // 117 4
    uint wheel_speed_right_rear;     // 121 4
    uint wheel_rotation_left_front;  // 125 4
    uint wheel_rotation_right_front; // 129 4
    uint wheel_rotation_left_rear;   // 133 4
    uint wheel_rotation_right_rear;  // 137 4
    uchar abs_active;                // 141 1
    uchar brake_activev;             // 142 1
    uchar esp_active;                // 143 1
    uint traction_control_active;    // 145 1
};

class RtvContext
{
public:
    RtvContext();
    virtual ~RtvContext();

    bool isReady() const;
    bool getFrame(int frameIndex, QImage& image);
    QImage* getFrame(int frameIndex);
    const Head& getHeadStruct() const;
    TagStruct getTagInfo(int index) const;
    bool initialize(const QString& rtvFilePath);
    void uninitialize();

    ImageBuffer& getImageBuffer();

    static double getNdsCoefficient();

private:
    bool setHeadData(const QByteArray& bytes);
    TagStruct getTagData(const QByteArray& bytes);

    void cleanTags();
    void cleanFrmaes();

private:
    static const int mHeadByteCount;
    static const double mNdsCoefficient;
    bool mIsReady;
    int mTagByteCount;
    QString mRtvFilePath;
    Head mHeadStruct;
    QVector<TagStruct> mTags;
    QVector<QImage*> mFrames;

    QFile mRtvFile;
    RtvImageLoader mLoader;
    ImageBuffer mBuffer;
};
qint64 bytesToInt(QByteArray bytes);
#endif // RTVCONTEXT_H
