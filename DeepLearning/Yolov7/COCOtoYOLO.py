import os 
import json
from tqdm import tqdm
import argparse
import random
import shutil

parser = argparse.ArgumentParser()
parser.add_argument('--json_path', default='./train.json',type=str, help="input: coco format(json)")
parser.add_argument('--save_path', default='./labels_yoloformat', type=str, help="specify where to save the output dir of labels")
arg = parser.parse_args()

def convert(size, box):
    dw = 1. / (size[0])
    dh = 1. / (size[1])
    x = box[0] + box[2] / 2.0
    y = box[1] + box[3] / 2.0
    w = box[2]
    h = box[3]

    x = x * dw
    w = w * dw
    y = y * dh
    h = h * dh
    return (x, y, w, h)



if __name__ == '__main__':
    json_file =   arg.json_path # COCO Object Instance類型的標註
    ana_txt_save_path = arg.save_path  # 保存的路徑

    data = json.load(open(json_file, 'r'))
    if not os.path.exists(ana_txt_save_path):
        os.makedirs(ana_txt_save_path)
    
    id_map = {} # coco數據及的id不連續！重新映射一下再输出！
    for i, category in enumerate(data['categories']): 
        id_map[category['id']] = i

    # 通過事先建表來降低時間複雜度
    max_id = 0
    for img in data['images']:
        max_id = max(max_id, img['id'])
    # 注意這裡不能寫 [[]]*(max_id+1)，否則列表内的空列表共享地址
    img_ann_dict = [[] for i in range(max_id+1)] 
    for i, ann in enumerate(data['annotations']):
        img_ann_dict[ann['image_id']].append(i)

    for img in tqdm(data['images']):
        filename = img["file_name"]
        img_width = img["width"]
        img_height = img["height"]
        img_id = img["id"]
        head, tail = os.path.splitext(filename)
        ana_txt_name = head + ".txt"  # 對應的txt名字，與jpg一致
        f_txt = open(os.path.join(ana_txt_save_path, ana_txt_name), 'w')
        # 這裡可以直接查表而無需重複遍歷
        for ann_id in img_ann_dict[img_id]:
            ann = data['annotations'][ann_id]
            box = convert((img_width, img_height), ann["bbox"])
            f_txt.write("%s %s %s %s %s\n" % (id_map[ann["category_id"]], box[0], box[1], box[2], box[3]))
        f_txt.close()