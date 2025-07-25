#    This file was created by
#    MATLAB Deep Learning Toolbox Converter for TensorFlow Models.
#    25-Jul-2025 17:42:01

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
    flatten = layers.Conv2D(2, (12,12), name="flatten_")(maxpool_2)
    softmax = layers.Softmax()(flatten)

    model = keras.Model(inputs=[input], outputs=[softmax])
    return model
