#    This file was created by
#    MATLAB Deep Learning Toolbox Converter for TensorFlow Models.
#    24-Jul-2025 17:18:21

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
    fc = layers.Reshape((1, 1, -1), name="fc_preFlatten1")(maxpool_2)
    fc = layers.Dense(2, name="fc_")(fc)
    softmax = layers.Softmax()(fc)
    output = layers.Flatten()(softmax)

    model = keras.Model(inputs=[input], outputs=[output])
    return model
