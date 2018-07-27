#include "custom_opcode.h"
#include <stddef.h>

EFI_STATUS
ReadFileToBuffer (
  IN  CHAR16                               *FileName,
  OUT UINTN                                *BufferSize,
  OUT VOID                                 **Buffer
  );

typedef struct _TestCaseElement
{
  UINT32 name_size;
  VOID *name;
  UINT32 value_size;
  VOID *value;
} TestCaseElement;

#define MAX_TCM_NUM 10
TestCaseElement current_tc[MAX_TCM_NUM];
UINT32 tce_num = 0;
UINT32 current_tce_idx = 0;

void *read_test_case_element(CHAR8 *buffer, TestCaseElement *tce/* , UNIT32 *buf_size_p */)
{
  UINT32 read_bytes = 0;
  /* UINT32 buf_size = *(UINT32 *)buf_size_p; */

  /* if(*buf_size < 4) */
  /*   goto error; */

  // 1. name_size
  read_bytes += 4;
  tce->name_size = *(UINT32 *)buffer;

  // 2. name
  buffer += 4;
  tce->name = buffer;

  // 3. value_size
  buffer += tce->name_size;
  tce->value_size = *(UINT32 *)buffer;

  // 4. value
  buffer += 4;
  tce->value = buffer;

  buffer += tce->value_size;

  return buffer;
}

void crete_ovmf_init(void)
{
  // 1. read crete tc from file to buffer
  CHAR8 *tcBuffer = NULL;
  UINTN FileSize = 0;
  EFI_STATUS Status;
  VOID *buf = (VOID *)tcBuffer;

  Status = ReadFileToBuffer((CHAR16 *)"next-tc.bin", &FileSize, &buf);
  if (EFI_ERROR(Status)) {
    Print(L"[ERROR] crete_ovmf_init(): read 'next-tc.bin' failed.\n");
    return;
  }
  tcBuffer = (CHAR8 *)buf;

  // 2. Parse buffer
  UINT32 elem_num = *(UINT32 *)tcBuffer;
  tcBuffer += 4;

  UINT32 count;
  for(count = 0; count < elem_num; ++count) {
    tcBuffer = read_test_case_element(tcBuffer, &current_tc[count]);
  }
}

void crete_make_concolic(void* addr, size_t size, const char* name)
{
  // TODO: XXX check name
  if(current_tc[current_tce_idx].value_size == size) {
    CopyMem(addr, current_tc[current_tce_idx].value, size);
  } else {
    Print(L"[ERROR] crete_make_concolic() failed.\n");
  }

  current_tce_idx++;
}

void crete_ovmf_finish(void)
{
}
