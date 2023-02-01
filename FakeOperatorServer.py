###
# Server listens on port 6666 for client requests
# Client sends "hello i'm alive" and "any requests for me?"
# Client goes into dictionary with unique ID
# {1:[192.168.1.11, ALIVE]}
##
import socket
import threading
import time    
import random

LOGO = """  ______    _           ____                       _             
 |  ____|  | |         / __ \                     | |            
 | |__ __ _| | _____  | |  | |_ __   ___ _ __ __ _| |_ ___  _ __ 
 |  __/ _` | |/ / _ \ | |  | | '_ \ / _ \ '__/ _` | __/ _ \| '__|
 | | | (_| |   <  __/ | |__| | |_) |  __/ | | (_| | || (_) | |   
 |_|__\__,_|_|\_\___|  \____/| .__/ \___|_|  \__,_|\__\___/|_|   
  / ____|                    | |                                 
 | (___   ___ _ ____   _____ |_|_                                
  \___ \ / _ \ '__\ \ / / _ \ '__|                               
  ____) |  __/ |   \ V /  __/ |                                  
 |_____/ \___|_|    \_/ \___|_|                                  
                                                                 
                                                                 """

youtube_list = [
    "W~https://www.youtube.com/watch?v=RGbaV6NlqMo~35000~",
    "W~https://www.youtube.com/watch?v=dQw4w9WgXcQ~212000~"
]
website_list = [
    "B~https://en.wikipedia.org/wiki/LOL",
    "B~https://www.bbc.co.uk/news"
]


client_dict = {}
job_dict = {}
client_amount = 0

def StartServer():
    global client_amount
    global client_dict
    HOST = "0.0.0.0"
    PORT = 6666
    
    # Set up socket for listening
    sock = socket.socket()
    sock.bind((HOST,PORT))
    sock.listen(3)
    
    # Client connected 
    conn, addr = sock.accept()
    clientIP = addr[0]
    epoch = int(time.time())
    #print("Client connected: %s" % (clientIP))
    
    # Checking is client in dict
    
    key_list = list(client_dict.keys())
    val_list = []
    
    # Iterating through dict due to using a list
    for k in key_list:
        val_list.append(client_dict[k][0])
    
    # Finds IP and updates the ALIVE part of list
    if clientIP in val_list:
        pos = val_list.index(clientIP)
        client_dict[pos + 1][0] = clientIP
        client_dict[pos + 1][1] = "ALIVE"
        client_dict[pos + 1][2] = epoch
        # If command slot has command, send that command
        if not client_dict[pos + 1][3] == "": SendCmds(pos + 1, conn)


    # Store new client details in dict
    if clientIP not in val_list:
        client_dict[client_amount + 1]=[clientIP, "ALIVE", epoch, "", ""]
        client_amount += 1
    
    
    #print("\n", client_dict)
    
    # Close socket
    sock.close()
    
def ListConns():
    global client_dict
    
    key_list = list(client_dict.keys())
    
    # Iterating through dict due to using a list
    for k in key_list:
        print("ID: %d IP: %s State: %s Level: %s" % (k,client_dict[k][0],client_dict[k][1], client_dict[k][4]))
    print("\n", client_dict)
    

    
def custom_youtube(key):
    global client_dict
    
    # Unique youtube ID
    v = input("Please enter the youtube V variable:\n")

    # Length of video change from 4:20 to 260,000
    length = input("Please enter the time e.g 4:20\n")
    
    # ["4","20"]
    length_split = length.split(":")
    minutes = int(length_split[0])
    seconds = (minutes * 60) + int(length_split[1])
    milli = seconds * 1000
    
    client_dict[key][3] = "W~https://www.youtube.com/watch?v=" + v + "~" + str(milli) + "~"
    
def custom_word(key):
    global client_dict
    
    text = input("Please enter the text you wish to type into word, use # for enter\n")
    
    client_dict[key][3] = "M~" + text
    
def custom_browse(key):
    global client_dict
    
    site = input("Please enter the website you want to view e.g. https://bbc.co.uk/news:\n")
    client_dict[key][3] = "B~" + site

def custom_powershell(key):
    global client_dict
    
    powershell = input("Please enter the powershell command:\n")
    client_dict[key][3] = "P~" + powershell
    
def Menu():
    global client_dict
    
    key_list = list(client_dict.keys())

    
    
    # CHANGE THIS TO LOOPS AND INCLUDE BACKS!
    choice = input('\n(1) List Connections (2) Set Level (3) Send Job: ')
    if choice == '1':
        ListConns()
    if choice == '2':
        key = ""
        while (key == ""):
            choice2 = input('\nL for List IDs or Enter ID number or * for all: ')
            if choice2.upper() == "L": ListConns()
            elif choice2 == "*":
                id_amount = list(client_dict.keys())
                choice = ""
                choiceDebug = input('\n(1) Low (2)Medium (3)High (4)BFT: ') #BFT = Big Fucking Traffic
                if choiceDebug == '1': choice = "Low"
                if choiceDebug == '2': choice = "Medium"
                if choiceDebug == '3': choice = "High"
                if choiceDebug == '4': choice = "BFT"  
                
                for k in key_list:
                    client_dict[k][4] = choice
                    
            else: key = int(choice2)
        if choice2 == '*':
            print("ALL")
        else:
            choiceDebug = input('\n(1) Low (2)Medium (3)High (4)BFT: ') #BFT = Big Fucking Traffic
            if choiceDebug == '1': client_dict[key][4] = "Low"
            if choiceDebug == '2': client_dict[key][4] = "Medium"
            if choiceDebug == '3': client_dict[key][4] = "High"
            if choiceDebug == '4': client_dict[key][4] = "BFT"           
        
    if choice == '3':
        key = ""
        while (key == ""):
            choice2 = input('\nL for List IDs or Enter ID number: ')
            if choice2.upper() == "L": ListConns()
            else: key = int(choice2)
        choice3 = input('\n(1) Youtube, (2) Word, (3) Browse Website (4) Powershell (5) Cancel Current Job: ')
        if choice3 == '1': custom_youtube(key)
        if choice3 == '2': custom_word(key)
        if choice3 == '3': custom_browse(key)
        if choice3 == '4': custom_powershell(key)
        if choice3 == '5': client_dict[key][4] = ""
        
    if choice == '4':
        print("########## DEBUG ##########")
        choiceDebug = input('\n(1) Website (2)Browse Site (3)Powershell (4)Word: ')
        if choiceDebug == '1': client_dict[1][3] = "W~https://www.youtube.com/watch?v=RGbaV6NlqMo~35000~"
        if choiceDebug == '2': client_dict[1][3] = "B~https://en.wikipedia.org/wiki/LOL"
        if choiceDebug == '3': client_dict[1][3] = "P~whoami"
        if choiceDebug == '4': client_dict[1][3] = "M~Site ton of characters here.#Blah blah blah#Yeah but no but.#"


        print(client_dict)

def TimeCheck():
    global client_dict

    epoch = time.time()    
    # Checking time isn't > 60 seconds

    key_list = list(client_dict.keys())
    val_list = []
    
    # Iterating through dict due to using a list
    for k in key_list:
        val_list.append(client_dict[k][2])
            
    # Check if epoch in dict is older than current time - 60 seconds (epoch_back)
    for t in val_list:
        diff = int(epoch - t)
        if diff >= 60:
            pos = val_list.index(t)
            client_dict[pos + 1][1]="DEAD"
    
    time.sleep(60)
    
def SendCmds(key, conn):
    global client_dict
    
    ip = client_dict[key][0]
    cmd = client_dict[key][3]

    print("Here Be Commands")
    
    # Finding in client_dict
    
   
   
    # Remove command from dict
    client_dict[key][3] = ""
    

    print("Sending %s to %s" % (cmd,ip))
    
    cmd = cmd.encode("utf")
    conn.sendall(cmd)
    # If connection has a list set send to function to set next command
    if client_dict[key][4]:
        NewCmd(key)
    
def NewCmd(key):
    global client_dict
    
    speed = client_dict[key][4]
    chance = random.randint(1,100)
    
    # Pick a random youtube and website in the list
    yt_r = random.randint(0, len(youtube_list) - 1)
    we_r = random.randint(0, len(website_list) - 1)
    
    youtube = youtube_list[yt_r]
    website = website_list[we_r]
    
    # Low - YT 20%, Word 30%, Browse 70%
    # Medium - YT 50%, Word 10%, Browse 40%
    # High - YT 90%, Browse 10%
    # BFT - Custom powershell commands and such 
    if(speed == "Low"):
        if(chance <= 20): client_dict[key][3] = youtube; print("YOUTUBE")
        if(chance >= 21 and chance <= 30): print("WORD")
        if(chance >= 31 and chance <= 100): client_dict[key][3] = website; print("WEBSITE")
    if(speed == "Medium"):
        if(chance <= 50): client_dict[key][3] = youtube; print("YOUTUBE")
        if(chance >= 51 and chance <= 60): client_dict[key][3] = website; print("WEBSITE")
        if(chance >= 61 and chance <= 100): print("BROWSE")
    if(speed == "High"):
        if(chance <= 90): client_dict[key][3] = youtube; print("YOUTUBE")
        if(chance >= 91 and chance <= 100): client_dict[key][3] = website; print("WEBSITE")
    if(speed == "BFT"): print("FUNCTION HERE")
    
    print(client_dict) 
    
def main():
    print(LOGO)
    print(youtube_list[0][1])
    
    thread = threading.Thread(target=StartServer)
    thread.daemon = True
    thread.start()
    
    thread2 = threading.Thread(target=Menu)
    thread2.daemon = True
    thread2.start()
    
    thread3 = threading.Thread(target=TimeCheck)
    thread3.daemon = True
    thread3.start()
    
    while True:        
        if not (thread.is_alive()):
          #  print("The thread is dead, long live the thread")
            thread = threading.Thread(target=StartServer)
            thread.daemon = True
            thread.start()
        if not (thread2.is_alive()):
           # print("The thread is dead, long live the thread")
            thread2 = threading.Thread(target=Menu)
            thread2.daemon = True
            thread2.start()
        if not (thread3.is_alive()):
           # print("The thread is dead, long live the thread")
            thread3 = threading.Thread(target=TimeCheck)
            thread3.daemon = True
            thread3.start()
    
                
if __name__ == "__main__":
    main()