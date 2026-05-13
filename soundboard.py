import pygame
import os
import random
from inputs import AudioInput, JoystickInput

class SFXLaunch:
    def __init__(self, launch_file):
        self.__launch_sound = pygame.mixer.Sound(launch_file)
        self.__launch_duration = 60

    def start_launch(self):
        self.__launch_sound.stop()
        self.__launch_sound.play(maxtime=self.__launch_duration*1000, fade_ms=50)

    def playing(self):
        return self.__launch_sound.get_num_channels() > 0

    def abort_launch(self):
        self.__launch_sound.stop()

class SFXOxygenTank:
    def __init__(self, sfx_folder, historical_sounds_folder):
        o2_path = os.path.join(sfx_folder, "StirOxygen.mp3")
        boom_path = os.path.join(sfx_folder, "mechanical_explosion.wav")
        houston_path = os.path.join(historical_sounds_folder, "Apollo13-wehaveaproblem_edit_1.ogg.mp3")

        self.__o2_stir = pygame.mixer.Sound(o2_path)
        self.__boom = pygame.mixer.Sound(boom_path)
        self.__houston = pygame.mixer.Sound(houston_path)
        self.__stir_duration = 3
        self.__stirring = False
        self.__booming = False
        self.problem_probability = 0.5

    def playing(self):
        return self.__o2_stir.get_num_channels() > 0 or self.__houston.get_num_channels() > 0 or self.__boom.get_num_channels() > 0

    def stir(self):
        print("STIR")
        if self.playing():
            return
        print("STIR")
        self.__stirring = True
        self.__o2_stir.play(maxtime=self.__stir_duration*1000, fade_ms=50)

    def update(self):
        if self.__o2_stir.get_num_channels() > 0 or self.__boom.get_num_channels() > 0 or self.__houston.get_num_channels() > 0:
            return
        if self.__stirring:
            self.__stirring = False
            if random.uniform(0,1) < self.problem_probability:
                self.__booming = True
                self.__boom.play()
        elif self.__booming:
            self.__booming = False
            self.__houston.play()

    def stop(self):
        self.__o2_stir.stop()
        self.__boom.stop()
        self.__houston.stop()

class SFXRandom:

    def __init__(self, sfx_folder, sfx_files):
        self.__sounds:list[pygame.mixer.Sound] = []
        for file in sfx_files:
            path = os.path.join(sfx_folder, file)
            self.__sounds.append(pygame.mixer.Sound(path))

    def play(self):
        for sound in self.__sounds:
            if sound.get_num_channels() > 0:
                return
            
        random.choice(self.__sounds).play(fade_ms=50)

    def playing(self):
        for sound in self.__sounds:
            if sound.get_num_channels() > 0:
                return True
        
        return False
    
    def stop(self):
        for sound in self.__sounds:
            sound.stop()

class QuindarTones:
    def __init__(self, sfx_folder):
        path_open = os.path.join(sfx_folder, "Quindar_Opening.ogg")
        path_close = os.path.join(sfx_folder, "Quindar_Closing.ogg")

        self.__open_tone = pygame.mixer.Sound(path_open)
        self.__close_tone = pygame.mixer.Sound(path_close)

    def open(self):
        self.__open_tone.play()

    def close(self):
        self.__close_tone.play()

class SFXThruster:
    def __init__(self, sfx_folder):
        path = os.path.join(sfx_folder, "ThrusterSounds.mp3")
        self.__sfx = pygame.mixer.Sound(path)
    
    def play(self):
        if self.__sfx.get_num_channels() == 0:
            self.__sfx.play(loops=-1)

    def stop(self):
        self.__sfx.stop()

    def update(self, joystick_input:JoystickInput):
        if joystick_input.x == 0 and joystick_input.y == 0 and joystick_input.z == 0:
            self.stop()
            return
        self.play()

class SFXDataUpload:
    def __init__(self, sfx_folder):
        path1 = os.path.join(sfx_folder, "DataUpload1.mp3")
        path2 = os.path.join(sfx_folder, "DataUpload2.mp3")
        path_send = os.path.join(sfx_folder, "DataUploadSend.mp3")

        self.__sfx1 = pygame.mixer.Sound(path1)
        self.__sfx2 = pygame.mixer.Sound(path2)
        self.__path_send = pygame.mixer.Sound(path_send)

        self.__send_max_time = 3

    def play_data1(self):
        if self.__sfx1.get_num_channels() == 0:
            self.__sfx1.play()
    
    def play_data2(self):
        if self.__sfx2.get_num_channels() == 0:
            self.__sfx2.play()

    def play_path_send(self):
        if self.__path_send.get_num_channels() == 0:
            self.__path_send.play(maxtime=self.__send_max_time*1000)

class Soundboard:
    def __init__(self, sounds_folder):

        general_historical_path = os.path.join(sounds_folder, "General_Historical")
        special_historical_path = os.path.join(sounds_folder, "Special_Historical")
        quindar_path = os.path.join(sounds_folder, "Quindar")
        sfx_path = os.path.join(sounds_folder, "SFX")

        self.__launch = SFXLaunch(os.path.join(special_historical_path, "Ap16_launch_trim.wav"))
        self.__random_historical = SFXRandom(general_historical_path, ["Aurora-7_Guyamas-Greeting.mp3", "Aurora-7_Guyamas-Greeting.mp3", "Discovery_-_Lookin_At_It.mp3.ogg", "Discovery_-_Press_to_ATO.mp3.ogg", "Mercury_6_-_Zero_G.mp3.ogg"])
        self.__quindar = QuindarTones(quindar_path)
        self.__stir = SFXOxygenTank(sfx_path, special_historical_path)
        self.__thruster = SFXThruster(sfx_path)
        self.__data_upload = SFXDataUpload(sfx_path)

    def random_historical(self):
        if not self.__launch.playing() and not self.__stir.playing():
            self.__random_historical.play()

    def launch(self):
        self.__random_historical.stop()
        self.__stir.stop()
        self.__launch.start_launch()

    def abort_launch(self):
        self.__launch.abort_launch()

    def stir(self):
        if not self.__launch.playing() and not self.__random_historical.playing():
            self.__stir.stir()

    def data1(self):
        self.__data_upload.play_data1()

    def data2(self):
        self.__data_upload.play_data2()

    def data_send(self):
        self.__data_upload.play_path_send()

    def update(self, audio_inputs:AudioInput, joystick_input:JoystickInput):
        for cmd in audio_inputs.audio_cmds:
            self.__process_cmd(cmd)
        self.__stir.update()
        self.__thruster.update(joystick_input)

    def __process_cmd(self, cmd:str):
        if "LAUNCH_START" in cmd:
            self.launch()
        if "LAUNCH_ABORT" in cmd:
            self.abort_launch()
        if "STIR" in cmd:
            self.stir()
        if "RANDOM_HISTORICAL" in cmd:
            self.random_historical()
        if "DATA_1" in cmd:
            self.data1()
        if "DATA_2" in cmd:
            self.data2()
        if "DATA_SEND" in cmd:
            self.data_send()
        