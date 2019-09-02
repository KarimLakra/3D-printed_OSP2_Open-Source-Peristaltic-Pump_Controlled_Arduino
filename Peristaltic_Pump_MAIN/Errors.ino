//reporting errors while reading SD card
char *verboseError(byte err)
{
  switch (err)
  {
  case ERROR_MBR_READ_ERROR:
    return "Error reading MBR";
    break;
  case ERROR_MBR_SIGNATURE:
    return "MBR Signature error";
    break;
  case ERROR_MBR_INVALID_FS:
    return "Unsupported filesystem";
    break;
  case ERROR_BOOTSEC_READ_ERROR:
    return "Error reading Boot Sector";
    break;
  case ERROR_BOOTSEC_SIGNATURE:
    return "Boot Sector Signature error";
    break;
  default:
    return "Unknown error";
    break;
  }
}
