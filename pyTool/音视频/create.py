from moviepy.editor import *
import configparser
def vedio_to_music(filepath,savepath):
    video = VideoFileClip(filepath)
    audio = video.audio
    audio.write_audiofile(savepath)