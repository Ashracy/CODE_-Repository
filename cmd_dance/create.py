from moviepy.editor import *
import configparser
cf= configparser.ConfigParser()
cf.read('config.ini')
filepath=cf.get('vedio','movie_path')
video = VideoFileClip(filepath)
audio = video.audio
audio.write_audiofile('temp.wav')