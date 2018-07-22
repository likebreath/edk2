#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/BmpSupportLib.h>
#include <Protocol/ShellParameters.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

// #include <Library/AFLLib.h>


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

  Blt = NULL;
  Width = 0;
  Height = 0;
  Status = TranslateBmpToGopBlt(BmpBuffer, FileSize, &Blt, &BltSize, &Height, &Width);
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
