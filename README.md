# LP-5
Practical Lab Sem-8 (SPPU Fourth Year Computer Engineering)

# HPC Assignment  (using OpenMP)

##  Compile and Run OpenMp in VS Code (Linux/GCC):

Step 1 : Make sure you have `g++` installed with OpenMP support.

### Compile:
g++ -fopenmp hpc.cpp -o hpc

### Run
./hpc





# Running a CUDA Program (`program.cu`)

## 🚀 **Steps to Compile and Run a CUDA Program**

### **1. Install CUDA Toolkit**

Before you can compile and run a CUDA program, make sure you have the **NVIDIA CUDA Toolkit** installed on your system. You can download it from the [NVIDIA CUDA website](https://developer.nvidia.com/cuda-downloads).

### **2. Compile the CUDA Program**

Once you have the CUDA Toolkit installed, open a terminal and navigate to the directory where your CUDA program (`program.cu`) is located.


```bash
nvcc program.cu -o program
```

> **Explanation:**
>
> * `nvcc` is the **NVIDIA CUDA Compiler**.
> * `program.cu` is your CUDA source file.
> * `-o program` specifies the output executable file name (`program`).

### **3. Run the CUDA Program**

```bash
./program
```

reg add "HKLM\SYSTEM\CurrentControlSet\Services\USBSTOR" /v Start /t REG_DWORD /d 3 /f
