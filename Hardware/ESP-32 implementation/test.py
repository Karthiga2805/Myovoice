import numpy as np
import tensorflow as tf

interpreter = tf.lite.Interpreter("emg_model.tflite")
interpreter.allocate_tensors()

input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

x = np.random.randint(-128, 127, size=input_details[0]['shape'], dtype=np.int8)
interpreter.set_tensor(input_details[0]['index'], x)
interpreter.invoke()

y = interpreter.get_tensor(output_details[0]['index'])
print(y)
