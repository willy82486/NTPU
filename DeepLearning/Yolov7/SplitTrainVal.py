import os
import random
import pandas as pd 
from sklearn.model_selection import train_test_split
from tqdm import tqdm
import glob
import shutil

# txt and img have to put into the same folder

def split_img_label(data_train, data_test, folder_train, folder_val):
    
    if not os.path.exists(folder_train):
        os.makedirs(folder_train)
    if not os.path.exists(folder_val):
        os.makedirs(folder_val)
    
    
    train_ind=list(data_train.index)
    test_ind=list(data_test.index)
    
    
    # Train folder
    for i in tqdm(range(len(train_ind))):
        
        # os.system('copy ' + data_train[train_ind[i]] + ' ' + folder_train + '/'  + data_train[train_ind[i]].split('/')[2])
        # os.system('copy ' + data_train[train_ind[i]].split('.jpg')[0] + '.txt' + ' '+ folder_train + '/'  + data_train[train_ind[i]].split('/')[2].split('.jpg')[0] +'.txt')
        shutil.copy(data_train[train_ind[i]], folder_train + '/'  + data_train[train_ind[i]].split('/')[2])
        shutil.copy(data_train[train_ind[i]].split('.jpg')[0] + '.txt', folder_train + '/'  + data_train[train_ind[i]].split('/')[2].split('.jpg')[0] +'.txt')
    # Val folder
    for j in tqdm(range(len(test_ind))):
        
        # os.system('copy ' + data_test[test_ind[j]] + ' ' + folder_val + '/'  +data_test[test_ind[j]].split('/')[2])
        # os.system('copy ' + data_test[test_ind[j]].split('.jpg')[0] + '.txt' + ' ' + folder_val + '/'  + data_test[test_ind[j]].split('/')[2].split('.jpg')[0] +'.txt')
        shutil.copy(data_test[test_ind[j]], folder_val + '/'  +data_test[test_ind[j]].split('/')[2])
        shutil.copy(data_test[test_ind[j]].split('.jpg')[0] + '.txt', folder_val + '/'  + data_test[test_ind[j]].split('/')[2].split('.jpg')[0] +'.txt')
if __name__ == '__main__':

    PATH = './trainingData/'
    folder_train_name = './train'
    folder_val_name = './val'
    list_img=[img for img in os.listdir(PATH) if img.endswith('.jpg')==True]
    list_txt=[img for img in os.listdir(PATH) if img.endswith('.txt')==True]

    path_img=[]

    for i in range (len(list_img)):
        path_img.append(PATH+list_img[i])
        
    df=pd.DataFrame(path_img)
    print(df)
    os.system("pause")
    # split 
    data_train, data_val, labels_train, labels_val = train_test_split(df[0], df.index, test_size=0.20, random_state=42)

    print(data_train)
    os.system("pause")
    # Function split 
    split_img_label(data_train, data_val, folder_train_name, folder_val_name)

