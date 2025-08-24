#    This file was created by
#    MATLAB Deep Learning Toolbox Converter for TensorFlow Models.
#    27-Jul-2025 02:12:47

import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers

def create_model():
    input = keras.Input(shape=(48,48,3))
    conv_1 = layers.Conv2D(8, (3,3), padding="same", name="conv_1_")(input)
    relu_1 = layers.ReLU()(conv_1)
    maxpool_1 = layers.MaxPool2D(pool_size=(2,2), strides=(2,2))(relu_1)
    conv_2 = layers.Conv2D(16, (3,3), padding="same", name="conv_2_")(maxpool_1)
    relu_2 = layers.ReLU()(conv_2)
    maxpool_2 = layers.MaxPool2D(pool_size=(2,2), strides=(2,2))(relu_2)
    gap = layers.GlobalAveragePooling2D(keepdims=True)(maxpool_2)
    conv_3 = layers.Conv2D(2, (1,1), name="conv_3_")(gap)
    softmax = layers.Softmax()(conv_3)

    model = keras.Model(inputs=[input], outputs=[softmax])
    return model
