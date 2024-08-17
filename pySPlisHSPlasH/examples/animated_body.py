import pysplishsplash as sph
import pysplishsplash.Utilities.SceneLoaderStructs as Scenes
import numpy as np
import math
from scipy.spatial.transform import Rotation as R
import os
import tkinter as tk
from tkinter import filedialog
import sys 

velocity = [0, 0, 0]

def time_step_callback():  
    sim = sph.Simulation.getCurrent()
    boundary = sim.getBoundaryModel(1)
    animatedBody = boundary.getRigidBodyObject()
    animatedBody.setVelocity([animatedBody.getVelocity()[i] + velocity[i] for i in range(3)])
    animatedBody.animate()
    
    #animatedBody.setAngularVelocity([0, 60.0/180.0*math.pi, 0])
    #animatedBody.animate()

def i():
    global velocity
    velocity = [0.1, 0, 0]
    print("velocity set to", velocity)

def k():
    global velocity
    velocity = [-0.1, 0, 0]
    print("velocity set to", velocity)

def j():
    pass

def l():
    pass

def main():
    # Set up the simulator
    tk.Tk().withdraw()
    scene_dir = os.path.join(os.path.dirname(sys.executable), "data/Scenes/")
    scene_file = filedialog.askopenfilename(initialdir=scene_dir)
    base = sph.Exec.SimulatorBase()
    base.init(useGui=True, useCache=False, sceneFile=scene_file)
    #pbd = sph.PBD.PBDBoundarySimulator(base)
    #base.setBoundarySimulator(pbd)
    #base.deferredInit()
    # Create an imgui simulator
    gui = sph.GUI.Simulator_GUI_imgui(base)
    base.setGui(gui)
    base.setTimeStepCB(time_step_callback)
    gui.addKeyFunc(73, 0 , i)
    gui.addKeyFunc(75, 0 , k)
    base.initSimulation()

    sim = sph.Simulation.getCurrent()
    sim.setValueInt(sim.BOUNDARY_HANDLING_METHOD, 0)

    base.runSimulation()
    base.cleanup()

if __name__ == "__main__":
    main()

