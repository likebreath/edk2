#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/BmpSupportLib.h>
#include <Protocol/ShellParameters.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

// #include <Library/AFLLib.h>
#include "crete-replay/custom_instr.c"
#define crete_buffer_size 100

EFI_STATUS test_TranslateBmpToGopBlt() {
  // Function Signature
  /*
RETURN_STATUS TranslateBmpToGopBlt (
        IN     VOID                           *BmpImage,
        IN     UINTN                          BmpImageSize,
        IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL  **GopBlt,
        IN OUT UINTN                          *GopBltSize,
        OUT    UINTN                          *PixelHeight,
        OUT    UINTN                          *PixelWidth
        )
  */

  EFI_STATUS                                    Status;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL                 *Blt;
  UINTN                                         BltSize;
  UINTN                                         Height;
  UINTN                                         Width;
  VOID                                          *BmpBuffer;
  UINTN                                      FileSize;


  BmpBuffer = 0;
  FileSize=0;

  // TODO: Bo, please make BmpBuffer and FileSize symbolic
  BmpBuffer = AllocateZeroPool(crete_buffer_size);
  /* FileSize = crete_buffer_size; */

  Blt = NULL;
  Width = 0;
  Height = 0;


  {
    crete_ovmf_init();

    crete_make_concolic((void *)BmpBuffer, crete_buffer_size, "BmpBuffer");
    crete_make_concolic(&FileSize, sizeof(FileSize), "FileSize");
    Status = TranslateBmpToGopBlt(BmpBuffer, FileSize, &Blt, &BltSize, &Height, &Width);

    crete_ovmf_finish();
  }

  return Status;
}

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

  test_TranslateBmpToGopBlt();

  return EFI_SUCCESS;
}
