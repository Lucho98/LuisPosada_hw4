# coding: utf-8
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D

data=np.loadtxt("Resultados_hw4.txt")
animacion=np.genfromtxt("animacion_hw4.txt")
tambor=np.genfromtxt("tambor.txt")


x=data[:,0]
u0=data[:,1]
u1=data[:,2]
u2=data[:,3]
u3=data[:,4]
u4=data[:,5]
u5=data[:,6]
u6=data[:,7]
u7=data[:,8]

plt.plot(x,u0,"r",label="t0")
plt.plot(x,u1,"b",label="t1")
plt.plot(x,u2,"g",label="t2")
plt.plot(x,u3,"y",label="t3")
plt.grid()
plt.legend()
plt.xlabel("x")
plt.ylabel("u")
plt.title("Onda Cuerda Extremos fijos")
plt.savefig("Cuerdaextremosfijos.pdf")
plt.close()


# In[72]:


plt.plot(x,u4,"r",label="t0")
plt.plot(x,u5,"b",label="t1")
plt.plot(x,u6,"g",label="t2")
plt.plot(x,u7,"y",label="t3")
plt.grid()
plt.legend()
plt.xlabel("x")
plt.ylabel("u")
plt.title("Onda Cuerda con perturbacion")
plt.savefig("Cuerdaperturbacion.pdf")
plt.close()

from scipy.io.wavfile import write
audio= np.loadtxt("audio.txt")
       

write('sonido.wav', 50000, audio)



N=len(animacion)/129
f=animacion[:,1]


m=f.reshape((1001,129)) 


fig = plt.figure()
ax = plt.axes(xlim=(0, 0.64), ylim=(-4, 4))

line, = ax.plot([], [], lw=2)

def init():
    line.set_data([], [])
    return line,

def update(i):
    x=np.linspace(0,0.64,129)
    y=m[i,:]
    line.set_data(x, y)
    return line,

ani = FuncAnimation(fig, update, frames=100,
                    init_func=init, blit=True)
ani.save('cuerda_animation.mp4', fps=20, extra_args=['-vcodec', 'libx264'])

t1=tambor[0:101,:]
t2=tambor[101:202,:]
t3=tambor[202:303,:]
t4=tambor[303:404,:]



plt.figure(1, figsize=(6, 6))
plt.subplots_adjust(left=0.05, right=0.95)
plt.subplot(221)
plt.imshow(t1)
plt.subplot(222)
plt.imshow(t2)
plt.colorbar()
plt.subplot(223)
plt.imshow(t3)
plt.subplot(224)
plt.imshow(t4)
plt.colorbar()
plt.savefig("tambor.pdf")
plt.close()

