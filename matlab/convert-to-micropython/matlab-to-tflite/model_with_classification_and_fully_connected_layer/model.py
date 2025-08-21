#    This file was created by
#    MATLAB Deep Learning Toolbox Converter for TensorFlow Models.
#    19-Aug-2025 18:44:58

import tensorflow as tf
from tensorflow import keras
from keras import layers

def create_model():
    imageinput_unnormalized = keras.Input(shape=(200,200,3), name="imageinput_unnormalized")
    imageinput = keras.layers.Normalization(axis=(1,2,3), name="imageinput_")(imageinput_unnormalized)
    conv_1 = layers.Conv2D(8, (3,3), padding="same", name="conv_1_")(imageinput)
    batchnorm_1 = layers.BatchNormalization(epsilon=0.000010, name="batchnorm_1_")(conv_1)
    relu_1 = layers.ReLU()(batchnorm_1)
    maxpool_1 = layers.MaxPool2D(pool_size=(2,2), strides=(2,2))(relu_1)
    conv_2 = layers.Conv2D(16, (3,3), padding="same", name="conv_2_")(maxpool_1)
    batchnorm_2 = layers.BatchNormalization(epsilon=0.000010, name="batchnorm_2_")(conv_2)
    relu_2 = layers.ReLU()(batchnorm_2)
    maxpool_2 = layers.MaxPool2D(pool_size=(2,2), strides=(2,2))(relu_2)
    fc = layers.Reshape((1, 1, -1), name="fc_preFlatten1")(maxpool_2)
    fc = layers.Dense(2, name="fc_")(fc)
    softmax = layers.Softmax()(fc)
    classoutput = layers.Flatten()(softmax)

    model = keras.Model(inputs=[imageinput_unnormalized], outputs=[classoutput])
    return model
