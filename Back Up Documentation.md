
Back Up documentation
========================

# NEA (Non Exam Assessment) - Designing a ISO image in low level languages to asses the state of computers


The problem: There is currently no super fast super efficient minimal OS system that low level programmers or system administrators can use to test if old computer can boot quickly. This can be especially problematic for organisation such as helppleasefixmycomputeritstopedworking because when they need to test if the computer is experience problems with the bios or with the main os system it is good to have a temporary live environment to boot quickly from just to ensure that the computer that helppleasefixmycomputeritstopedworking is fixing is not experiencing problems with the bios or initial booting. helppleasefixmycomputeritstopedworking is also a relatively small company with only 4 employs The_Boss, Employ_1, Employ_2 and Steveo. Steveo is the only low level programmer to work at this company because of this he is in change of ensuring that the computers that helppleasefixmycomputeritstopedworking are fixing are not experiencing problems with there bios because that is an issues that is very difficult to fix. the reason poor Steveo can not use a pre-existing OS like ubuntu to load on is because it is slow AF on old machines this was not a problem when the company first started out and got at most 1 PC a day but now helppleasefixmycomputeritstopedworking is getting many computers due to a recent power serge in the area now Steveo has to deal with lots and lots of computers that all may have had there BIOS chip fried it is now his job to find a way to quickly test all of these computers and test them quickly.

## Background 

The organisation in this project is called helppleasefixmycomputeritstopedworking. It is a small computer repair business that specialises in diagnosing and fixing hardware and software problems in desktop PCs and laptops. The company is based in a local community that has recently suffered from a major power surge, resulting in a sudden increase in damaged or non-booting computers.

The business has only four employees:

    The_Boss – Oversees the business and handles customer service

    Employ_1 (Daron) – General technician

    Employ_2 – General technician

    Steveo – Low-level systems programmer

Due to the recent increase in demand, the team now receives many more machines per day—some of which may have BIOS-level faults or other early boot problems.

Steveo is responsible for identifying whether each incoming computer can successfully power on, reach the BIOS, and begin the boot process. However, this is currently slow and inefficient, because there is no ultra-lightweight, high-speed, minimal operating system that can boot quickly enough to verify that a system is functioning at a basic level.

Existing operating systems such as Ubuntu or Windows PE are too slow to boot in this quick paced environment, and many of these damaged systems may not have the resources to support them. When the company only received one PC a day, this was manageable. But now, Steveo is overwhelmed.

The goal of this project is to create a custom minimal OS, designed to boot quickly and give immediate feedback as to whether a computer is functioning at a low level. This would allow Steveo (the project’s main contact) to rapidly triage incoming machines and prioritise repairs.

## Description of Current System

At the moment Steveo is using a light weight version of ubuntu called Xubuntu witch runs minimal software and uses Xfce for the gui to further decrease processing power. However form Steveos own experience and general consensus from online form surrounding Xubuntu the boot time could take as long as 4 minuets and according to one source the 

“boot time was never less than 30 seconds always between 30‑50 seconds” ~ *https://itsfoss.community/t/linux-boot-time-is-more-than-windows-boot-time-on-old-laptop-pc/7343/1 a comment made by user **Mohit Bora*** 

because of this a task that could be taking Steveo a mere 20 seconds is taking him sometimes 4+ minuets a waste of time in The_Boss's eyes. Even more detail about the current system:
Xubuntu is a Linux distro based off of Ubuntu this worked well initially because of how easy it was for Steveo to flash the Xubuntu ISO on to a USB flash drive it was also a freely available tool and has lots of systems and pre-built commands that help with other testing later on. In my project i do not think I will be able to tackle all of the issues with it explicitly later on testing of the system with some of the tools Xubuntu has however I believe that I will be able to test if a system has BIOS problems and early on booting problems and test if the computer can run a simple program and if the system has I/O problems. Recap of problems I hope to solve:

      speeding up testing

      checking for BIOS problems  

      checking for early stage problems 

      checking for I/O problems  

      checking for ability to run simple scripts/programs

## Identification of User and Users needs and acceptable limitations

The main user of my project will be low level system programmers and computer repair shop workers this is because the UI may be unfriendly to the average computer user and these types of people simply would not have the use cases necessary to go through the effort of installing the OS. Only one person should be be using an instance of the OS at a time and as this is effectively a testing ground for technicians there is no need for there to be instance of multiple users on the OS this should mean that it is much easier to programmer as I do not need a databases stored in memory of each user on the OS.

I believed the needs of the user are very simple to establish an OS that a user can boot into from a USB to test basic functionality of there system ensuring their BIOS there early booting stage and they keyboard all work correctly. to make sure I correctly identify the metrics Steveo needed I did a Q&A with him asking all the important question here is a transcription of the core parts of our conversation (I asked the questions and Steveo answered them)

Q: What is your need for this Operating system?

A: Well the company I work at (the computer repair shop) needs me to test computers to ensure that there is not booting, keyboard and BIOS issues and if these issues are they identifying what they are. 

Q: Do you already have a system in place to find deal with this issue

A: Yes we do actually but it really sucks. It is slow to boot has way to much stuff on it for the testing I need to do and end up spending like 1 minuet once the device has booted up testing what i need to test.

Q: What features or tools do you absolutely need the OS to have to make your job easier?

A: Hello

Q: Are there any specific hardware components or brands that the OS must support or be compatible with?

A: Hello

Q: How important is the boot speed of the OS to you? What is an acceptable maximum boot time?

A: Hello

Q: How would you prefer to navigate and interact with the OS? Command line, graphical interface, or both?

A: Hello

Q: Are there any common issues or errors you encounter frequently during testing that you want the OS to help diagnose automatically?

A: Hello

Q: Would you require the OS to save any logs or test results? If yes, how should these be accessed or stored?

A: Hello

Q: What limitations would you find acceptable in this OS? For example, lack of multi-user support or limited software?

A: Hello

Q: How important is portability for this OS? Should it work on as many different machines as possible, or just a specific set?

A: Hello

Q: How would you rate your technical skill level and comfort with installing and using a custom OS from USB?

A: Hello

Q: What is the most frustrating part of your current testing process that you want this OS to fix?

A: Hello

Q: Would you like the OS to have any diagnostic visualization (e.g., showing keyboard inputs, BIOS messages)?

A: Hello

Q: Are there any security concerns or precautions you want for this OS, given it might be used on multiple potentially faulty machines?

A: Hello


## Data Source and Volumes



## Modelling (Data Dictionary, ERD, data flow, etc.)



## Objectives and Requirements



