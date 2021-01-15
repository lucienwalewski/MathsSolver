from keras.models import load_model
import pandas as pd
from PIL import Image, ImageOps
# import CharacterSegmentation as cs
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure
import matplotlib.image as mpimg
import os



import os

os.environ['KMP_DUPLICATE_LIB_OK']='True'

SEGMENTED_OUTPUT_DIR = './extractedImages/'
# EMNIST_PATH = './data/emnist/'
MODEL_PATH = './model/alphanum_model_binary_ex_88.h5'
mapping_processed = './model/processed-mapping.csv'

segmented_images = []
files = [f for r, d, f in os.walk(SEGMENTED_OUTPUT_DIR)][0]
for f in files:
    segmented_images.append(Image.open(SEGMENTED_OUTPUT_DIR + f))

# figure(figsize=(18,18))
#
# size = len(segmented_images)
# for i in range(size):
#     img = segmented_images[i]
#     imgplot = plt.imshow(img)
#     plt.subplot(2, size, i + 1)
#     plt.show()
#     # plt.show(img)
#     # plt.figure(img)
#     # plt.imshow(img)


import cv2
import numpy as np

files = [f for r, d, f in os.walk(SEGMENTED_OUTPUT_DIR)][0]
for f in files:
    filename = SEGMENTED_OUTPUT_DIR + f
    img = cv2.imread(filename, 0)

    kernel = np.ones((2, 2), np.uint8)
    dilation = cv2.erode(img, kernel, iterations=1)
    cv2.imwrite(filename, dilation)


def img2emnist(filepath, char_code):
    img = Image.open(filepath).resize((28, 28))
    inv_img = ImageOps.invert(img)

    flatten = np.array(inv_img).flatten()
    flatten = flatten / 255
    flatten = np.where(flatten > 0.5, 1, 0)

    csv_img = ','.join([str(num) for num in flatten])
    csv_str = '{},{}'.format(char_code, csv_img)
    return csv_str


temp_filename = 'test.csv'
if os.path.exists(temp_filename):
    os.remove(temp_filename)

f_test = open(temp_filename, 'a+')
column_names = ','.join(["label"] + ["pixel" + str(i) for i in range(784)])
print(column_names, file=f_test)

files = [f for r, d, f in os.walk(SEGMENTED_OUTPUT_DIR)][0]
for f in files:
    csv = img2emnist(SEGMENTED_OUTPUT_DIR + f, -1)
    print(csv, file=f_test)

f_test.close()

test_df = pd.read_csv(temp_filename)
test_df

data = pd.read_csv(temp_filename)
X_data = data.drop(labels=["label"], axis=1)
X_data = X_data.values.reshape(-1, 28, 28, 1)

# figure(figsize=(14, 14))

# size = X_data.shape[0]
# for i in range(size):
#     v = X_data[i][:, :, 0].astype('uint8')
#     img = Image.fromarray(255 * v)
#
#     plt.subplot(2, size, i + 1)
#     plt.imshow(img)


df = pd.read_csv(mapping_processed)
code2char = {}
for index, row in df.iterrows():
    code2char[row['id']] = row['char']


model = load_model(MODEL_PATH)


# predict results
results = model.predict(X_data)
# print(results)

# select the index with the maximum probability
results = np.argmax(results, axis=1)
print(results)
parsed_str = ""
for r in results:
    parsed_str += code2char[r]

# print(parsed_str)
parsed_str
