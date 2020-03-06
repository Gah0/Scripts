import tkinter as tk

class App:
    def __init__(self,root):
        frame = tkFrame(root)
        frame.pack()
        self.hey_there = tk.Button(frame,text="打招呼",fg = command = self.say_hey)
        self.hey_there.pack(side=tk.LEFT)

    def say_hey(self):
        print("你好，我叫林佳语")

root = tk.Tk()
app = App(root)

root.mainloop()