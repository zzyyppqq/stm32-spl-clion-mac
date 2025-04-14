# STM32 + Clion新建工程：标准库

### STM32 SPL startup的arm、gcc_ride7、iar、TrueSTUDIO


| 工具链         | 文件扩展名 | 注释符号 | 语法标准          | 典型应用场景      |
| -------------- | ---------- | -------- | ----------------- | ----------------- |
| **ARM MDK**    | `.s`       | `;`      | ARM汇编           | Keil开发环境13    |
| **GCC**        | `.S`       | `#`或`;` | GNU汇编           | 跨平台开源项目6   |
| **IAR**        | `.s`       | `;`      | IAR汇编           | 商业高可靠性项目9 |
| **TrueSTUDIO** | `.S`       | `#`      | GNU汇编（预处理） | STM32CubeIDE46    |

### core_cm3.c文件修改

[core_cm3.c文件修改](./images/strexb.png)