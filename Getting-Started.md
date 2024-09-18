
# Setting Up 

PlatformIO is the IDE we will be using program our bot using the Arduino framework. PlatformIO has lot of integration with VSCode, so we highly 
recommend VSCode as our code editor of choice. If you do not have VSCode installed already the link to the download page can be found at this [link](https://code.visualstudio.com/).

# Installing PlatformIO

  1. Go to [PlatformIO website](https://platformio.org/platformio-ide)

  2. Click on "Get for VSCode" button and follow download instructions 

# Creating new projects 

  1. Easiest way is to click on PlatformIO icon on the left toolbar and go to "PIO Home" 

  2. Select "New Project" 

  3. Choose the board your project is using (e.g. STM32, ESP32, or Arduino board).  

  4. Select the Arduino Framework

Your project should now include a list of directories along with a `platform.ini` file filled with the settings you chose earlier. 
If you want to learn more about how to add different configurations to this file you can follow this link to the PlatformIO [Docs](https://docs.platformio.org/en/latest/).

# Git setup 

Git/Github provides a way for multiple people to collaborate on one project and manage version control. You can use Github with the CLI or by using VSCode's built-in Git commands. If you are new to Github, you can follow this handy [tutorial](https://docs.github.com/en/get-started/start-your-journey/hello-world) 

Generally the workflow of Git consists of the following: 

  1. `git pull` (pulls the most recent code from the Github repo) 
  2. Write code
  3. `git add .` (to add code to the repo)
  4. `git commit -m "Short and descriptive message"`
  5. `git push` (to send your code to GitHub)

If working on the main repository, please use `git branch [branch name]` to start a branch and `git checkout [branch name]` to switch to it. You could combine these steps with `git checkout -b [branch name]` as a shorthand. 
