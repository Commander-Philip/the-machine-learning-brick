import onnx

model = onnx.load('3070er.onnx')
graph = model.graph
for input_tensor in graph.input:
    print("Input Name: ",input_tensor.name)
    print("Tensor Type:", input_tensor.type)
