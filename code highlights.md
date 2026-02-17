# code highlights

```  
OS-build  

├── Makefile  
├── source  
    ├── colours  
        └── print.h  
    └── impl  
        ├── kernel  
        │   └── main.c  
        └── x86_64  
            ├── print.c    
            ├── keyboard.c   
            ├── test_program.c 
            └── boot  
                ├── header.asm  
                ├── main.asm  
                └── main64.asm  
├── targets-x86_64  
    ├── linker.ld  
    └── boot  
        ├── kernel.bin  
        └── grub  
            └── grub.cfg  
└── distribution-x86_64  
    ├── kernel.bin  
    └── kernel.iso 
```  



### Key Highlights in print.c

#### 1️⃣ VGA Memory Writing

- The `buffer` pointer directly references VGA text-mode memory at `0xb8000`.
- Each screen character is represented as a struct:

```c
struct Char {
    uint8_t character;
    uint8_t color;
};
```

