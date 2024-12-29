import json
import os
import shutil
from os import listdir
from os.path import isfile
from os.path import join
import argparse
import funcy
from sklearn.model_selection import train_test_split
from skmultilearn.model_selection import iterative_train_test_split
import numpy as np

img_path = 'images/'
output_dir = 'YoloX_dataset/'
jsons_path = os.path.join(output_dir, 'annotations/')
train_imgs_path = os.path.join(output_dir, 'train_img/')
val_imgs_path = os.path.join(output_dir, 'test_img/')

if not os.path.exists(output_dir):
    os.makedirs(jsons_path)
    os.makedirs(train_imgs_path)
    os.makedirs(val_imgs_path)
fileName = [file for file in listdir(img_path) if isfile(join(img_path, file))]



def save_coco(file, images, annotations, categories):
    with open(file, 'wt', encoding='UTF-8') as coco:
        json.dump({'images': images, 
            'annotations': annotations, 'categories': categories}, coco, indent=2, sort_keys=True)

def filter_annotations(annotations, images, splitImg):
    image_ids = funcy.lmap(lambda i: int(i['id']), images)
    filter_anno = funcy.lfilter(lambda a: int(a['image_id']) in image_ids, annotations)
    if splitImg ==1 :
        img_name = funcy.lmap(lambda i: i['file_name'], images)
        train = 0
        test = 0
        for file in listdir(img_path):
            flag = 0
            for img in img_name:
                if file==img:
                    #print("file: "+ file)
                    #print("img: " + img)
                    shutil.copy(img_path + '/' + file , train_imgs_path + '/' + file)
                    flag = 1
                    train += 1
                    break
            if flag == 0:
                shutil.copy(img_path + '/' + file , val_imgs_path + '/' + file)
                test += 1
        print("filter_annotations function")
        print("train image: " + str(train))
        print("test image: " + str(test))
    return filter_anno


def filter_images(images, annotations, splitImg):

    annotation_ids = funcy.lmap(lambda i: int(i['image_id']), annotations)
    img = funcy.lfilter(lambda a: int(a['id']) in annotation_ids, images)
    if splitImg ==1 :
        img_name = funcy.lmap(lambda i: i['file_name'], img)
        train = 0
        test = 0
        for file in listdir(img_path):
            flag = 0
            for img in img_name:
                if file==img:
                    #print("file: "+ file)
                    #print("img: " + img)
                    shutil.copy(img_path + '/' + file , train_imgs_path + '/' + file)
                    flag = 1
                    train += 1
                    break
            if flag == 0:
                shutil.copy(img_path + '/' + file , val_imgs_path + '/' + file)
                test += 1
        print("train image: " + str(train))
        print("test image: " + str(test))
    return img 


parser = argparse.ArgumentParser(description='Splits COCO annotations file into training and test sets.')
parser.add_argument('annotations', metavar='coco_annotations', type=str,
                    help='Path to COCO annotations file.')
parser.add_argument('train', type=str, help='Where to store COCO training annotations')
parser.add_argument('test', type=str, help='Where to store COCO test annotations')
parser.add_argument('-s', dest='split', type=float, required=True,
                    help="A percentage of a split; a number in (0, 1)")
parser.add_argument('--having-annotations', dest='having_annotations', action='store_true',
                    help='Ignore all images without annotations. Keep only these with at least one annotation')

parser.add_argument('--multi-class', dest='multi_class', action='store_false',
                    help='Split a multi-class dataset while preserving class distributions in train and test sets')

args = parser.parse_args()

def main(args):

    with open(args.annotations, 'rt', encoding='UTF-8') as annotations:
        coco = json.load(annotations)
        images = coco['images']
        annotations = coco['annotations']
        categories = coco['categories']

        number_of_images = len(images)

        images_with_annotations = funcy.lmap(lambda a: int(a['image_id']), annotations)

        if args.having_annotations:
            images = funcy.lremove(lambda i: i['id'] not in images_with_annotations, images)


        if args.multi_class:

            annotation_categories = funcy.lmap(lambda a: int(a['category_id']), annotations)

            #bottle neck 1
            #remove classes that has only one sample, because it can't be split into the training and testing sets
            annotation_categories =  funcy.lremove(lambda i: annotation_categories.count(i) <=1  , annotation_categories)

            annotations =  funcy.lremove(lambda i: i['category_id'] not in annotation_categories  , annotations)


            X_train, y_train, X_test, y_test = iterative_train_test_split(np.array([annotations]).T,np.array([ annotation_categories]).T, test_size = 1-args.split)

            save_coco(args.train, filter_images(images, X_train.reshape(-1), 1), X_train.reshape(-1).tolist(), categories)
            save_coco(args.test, filter_images(images, X_test.reshape(-1), 0), X_test.reshape(-1).tolist(), categories)

            print("multi_class\nSaved {} entries in {} and {} in {}".format(len(X_train), args.train, len(X_test), args.test))
            
        else:

            X_train, X_test = train_test_split(images, train_size=args.split)

            anns_train = filter_annotations(annotations, X_train, 1)
            anns_test=filter_annotations(annotations, X_test, 0)

            save_coco(args.train, X_train, anns_train, categories)
            save_coco(args.test, X_test, anns_test, categories)

            print("No multi_class\nSaved {} entries in {} and {} in {}".format(len(anns_train), args.train, len(anns_test), args.test))
            


if __name__ == "__main__":
    main(args)



# def save_coco(file, info, licenses, images, annotations, categories):
#     with open(file, 'wt', encoding='UTF-8') as coco:
#         json.dump({ 'info': info, 'licenses': licenses, 'images': images, 
#             'annotations': annotations, 'categories': categories}, coco, indent=2, sort_keys=True)

# def filter_annotations(annotations, images):
#     image_ids = funcy.lmap(lambda i: int(i['id']), images)
#     return funcy.lfilter(lambda a: int(a['image_id']) in image_ids, annotations)


# def filter_images(images, annotations):

#     annotation_ids = funcy.lmap(lambda i: int(i['image_id']), annotations)

#     return funcy.lfilter(lambda a: int(a['id']) in annotation_ids, images)


# parser = argparse.ArgumentParser(description='Splits COCO annotations file into training and test sets.')
# parser.add_argument('annotations', metavar='coco_annotations', type=str,
#                     help='Path to COCO annotations file.')
# parser.add_argument('train', type=str, help='Where to store COCO training annotations')
# parser.add_argument('test', type=str, help='Where to store COCO test annotations')
# parser.add_argument('-s', dest='split', type=float, required=True,
#                     help="A percentage of a split; a number in (0, 1)")
# parser.add_argument('--having-annotations', dest='having_annotations', action='store_true',
#                     help='Ignore all images without annotations. Keep only these with at least one annotation')

# parser.add_argument('--multi-class', dest='multi_class', action='store_true',
#                     help='Split a multi-class dataset while preserving class distributions in train and test sets')

# args = parser.parse_args()

# def main(args):

#     with open(args.annotations, 'rt', encoding='UTF-8') as annotations:
#         coco = json.load(annotations)
#         info = coco['info']
#         licenses = coco['licenses']
#         images = coco['images']
#         annotations = coco['annotations']
#         categories = coco['categories']

#         number_of_images = len(images)

#         images_with_annotations = funcy.lmap(lambda a: int(a['image_id']), annotations)

#         if args.having_annotations:
#             images = funcy.lremove(lambda i: i['id'] not in images_with_annotations, images)


#         if args.multi_class:

#             annotation_categories = funcy.lmap(lambda a: int(a['category_id']), annotations)

#             #bottle neck 1
#             #remove classes that has only one sample, because it can't be split into the training and testing sets
#             annotation_categories =  funcy.lremove(lambda i: annotation_categories.count(i) <=1  , annotation_categories)

#             annotations =  funcy.lremove(lambda i: i['category_id'] not in annotation_categories  , annotations)


#             X_train, y_train, X_test, y_test = iterative_train_test_split(np.array([annotations]).T,np.array([ annotation_categories]).T, test_size = 1-args.split)

#             save_coco(args.train, info, licenses, filter_images(images, X_train.reshape(-1)), X_train.reshape(-1).tolist(), categories)
#             save_coco(args.test, info, licenses,  filter_images(images, X_test.reshape(-1)), X_test.reshape(-1).tolist(), categories)

#             print("Saved {} entries in {} and {} in {}".format(len(X_train), args.train, len(X_test), args.test))
            
#         else:

#             X_train, X_test = train_test_split(images, train_size=args.split)

#             anns_train = filter_annotations(annotations, X_train)
#             anns_test=filter_annotations(annotations, X_test)

#             save_coco(args.train, info, licenses, X_train, anns_train, categories)
#             save_coco(args.test, info, licenses, X_test, anns_test, categories)

#             print("Saved {} entries in {} and {} in {}".format(len(anns_train), args.train, len(anns_test), args.test))
            


# if __name__ == "__main__":
#     main(args)