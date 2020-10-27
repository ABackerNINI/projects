#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//隐藏运行

size_t clipboard_read(char* buff, size_t bufsz) {
    //局部变量
    char* pbuf = NULL;
    size_t i;

    HANDLE hclip;  //剪切板句柄

    //剪切板当中的数据是不是文本类型的
    if (!IsClipboardFormatAvailable(CF_TEXT)) {
        return -1;
    }

    //打开剪切板，获取里面的数据
    if (OpenClipboard(NULL) == 0) {
        printf("打开剪切板失败！\n");
        return -1;
    }

    //获取剪切板里面的数据
    hclip = GetClipboardData(CF_TEXT);
    if (!hclip) {
        printf("读取错误!\n");
        CloseClipboard();
        return -1;
    }
    pbuf = (char*)GlobalLock(hclip);  //加锁，返回一个VOID类型的指针
    if (!pbuf) {
        printf("读取错误!\n");
        CloseClipboard();
        return -1;
    }
    GlobalUnlock(hclip);              //解锁
    //测试剪切板是否能使用

    i = 0;
    while (*pbuf && i < bufsz - 1) {
        if ((*pbuf >= 0 && *pbuf <= 255 && isalnum(*pbuf)) || *pbuf == ':' || *pbuf == '/') {
            buff[i++] = *pbuf;
        }
        ++pbuf;
    }
    buff[i] = '\0';

    CloseClipboard();  //关闭剪切板，不然其他程序无法正常0使用剪切板

    return i;
}

int clipboard_write(const char* content) {
    HGLOBAL hMemory;
    LPTSTR lpMemory;
    size_t contentSize = strlen(content) + 1;

    if (!OpenClipboard(NULL))  // 打开剪切板，打开后，其他进程无法访问
    {
        puts("剪切板打开失败");
        return 1;
    }

    if (!EmptyClipboard())  // 清空剪切板，写入之前，必须先清空剪切板
    {
        puts("清空剪切板失败");
        CloseClipboard();
        return 1;
    }

    if ((hMemory = GlobalAlloc(GMEM_MOVEABLE, contentSize)) ==
        NULL)  // 对剪切板分配内存
    {
        puts("内存赋值错误!!!");
        CloseClipboard();
        return 1;
    }

    if ((lpMemory = (LPTSTR)GlobalLock(hMemory)) == NULL)  // 将内存区域锁定
    {
        puts("锁定内存错误!!!");
        CloseClipboard();
        return 1;
    }

    memcpy_s(lpMemory, contentSize, content,
        contentSize);  // 将数据复制进入内存区域

    GlobalUnlock(hMemory);  // 解除内存锁定

    if (SetClipboardData(CF_TEXT, hMemory) == NULL) {
        puts("设置剪切板数据失败!!!");
        CloseClipboard();
        return 1;
    }
    return 0;
}

int read_date_time(const char* buff, int& yy, int& mm, int& dd, int& h, int& m, int& s) {
    if (sscanf(buff, "%4d/%2d/%2d%2d:%2d:%2d", &yy, &mm, &dd, &h, &m, &s) >= 5) {
        return 1;
    }
    return 0;
}

void fout(const char* filepath, const char* s) {
    FILE* fp = fopen(filepath, "a");
    if (fp) {
        fprintf(fp, "DateTime: %s\n", s);
        fclose(fp);
    }
    else {
        perror("fopen");
    }
}

int main(int argc, char* argv[]) {
    char buff[3][64], * pbuff, * oldbuff;
    int yy, mm, dd, h, m, s;
    size_t len, oldlen = 0;


    const char* log_path = "C:/NINI/ClipboardDateTime/log.log";

    remove(log_path);

    pbuff = buff[0];
    oldbuff = buff[1];
    while (1) {
        if ((len = clipboard_read(pbuff, 64)) >= 18 && len < 64) {
            if (!(len == oldlen && strcmp(pbuff, oldbuff) == 0)) {
                yy = mm = dd = h = m = s = 0;
                if (read_date_time(pbuff, yy, mm, dd, h, m, s)) {
                    sprintf(buff[2], "%4d/%02d/%02d %02d:%02d:%02d", yy, mm, dd, h, m, s);
                    printf("DateTime: %s\n", buff[2]);
                    fout(log_path, buff[2]);
                    clipboard_write(buff[2]);

                    oldbuff = pbuff;
                    oldlen = len;
                    pbuff = (pbuff == buff[0] ? buff[1] : buff[0]);
                }
            }
        }
        Sleep(1000);
    }

    return 0;
}