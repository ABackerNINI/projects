#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//��������

size_t clipboard_read(char* buff, size_t bufsz) {
    //�ֲ�����
    char* pbuf = NULL;
    size_t i;

    HANDLE hclip;  //���а���

    //���а嵱�е������ǲ����ı����͵�
    if (!IsClipboardFormatAvailable(CF_TEXT)) {
        return -1;
    }

    //�򿪼��а壬��ȡ���������
    if (OpenClipboard(NULL) == 0) {
        printf("�򿪼��а�ʧ�ܣ�\n");
        return -1;
    }

    //��ȡ���а����������
    hclip = GetClipboardData(CF_TEXT);
    if (!hclip) {
        printf("��ȡ����!\n");
        CloseClipboard();
        return -1;
    }
    pbuf = (char*)GlobalLock(hclip);  //����������һ��VOID���͵�ָ��
    if (!pbuf) {
        printf("��ȡ����!\n");
        CloseClipboard();
        return -1;
    }
    GlobalUnlock(hclip);              //����
    //���Լ��а��Ƿ���ʹ��

    i = 0;
    while (*pbuf && i < bufsz - 1) {
        if ((*pbuf >= 0 && *pbuf <= 255 && isalnum(*pbuf)) || *pbuf == ':' || *pbuf == '/') {
            buff[i++] = *pbuf;
        }
        ++pbuf;
    }
    buff[i] = '\0';

    CloseClipboard();  //�رռ��а壬��Ȼ���������޷�����0ʹ�ü��а�

    return i;
}

int clipboard_write(const char* content) {
    HGLOBAL hMemory;
    LPTSTR lpMemory;
    size_t contentSize = strlen(content) + 1;

    if (!OpenClipboard(NULL))  // �򿪼��а壬�򿪺����������޷�����
    {
        puts("���а��ʧ��");
        return 1;
    }

    if (!EmptyClipboard())  // ��ռ��а壬д��֮ǰ����������ռ��а�
    {
        puts("��ռ��а�ʧ��");
        CloseClipboard();
        return 1;
    }

    if ((hMemory = GlobalAlloc(GMEM_MOVEABLE, contentSize)) ==
        NULL)  // �Լ��а�����ڴ�
    {
        puts("�ڴ渳ֵ����!!!");
        CloseClipboard();
        return 1;
    }

    if ((lpMemory = (LPTSTR)GlobalLock(hMemory)) == NULL)  // ���ڴ���������
    {
        puts("�����ڴ����!!!");
        CloseClipboard();
        return 1;
    }

    memcpy_s(lpMemory, contentSize, content,
        contentSize);  // �����ݸ��ƽ����ڴ�����

    GlobalUnlock(hMemory);  // ����ڴ�����

    if (SetClipboardData(CF_TEXT, hMemory) == NULL) {
        puts("���ü��а�����ʧ��!!!");
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