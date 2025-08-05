import tensorflow as tf
import tf_model as tf_model

model = tf_model.load_model()
layerIndex = tf_model.layerNum(model, 'softmax')
print(f"Layer-Index: {layerIndex}")
print(f"Model: {model}")
concrete_func = model.signatures["serving_default"]

print("Inputs:", concrete_func.inputs)
print("Outputs:", concrete_func.outputs)

for op in concrete_func.graph.get_operations():
    print(op.name)
