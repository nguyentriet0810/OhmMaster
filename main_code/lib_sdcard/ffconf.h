/*---------------------------------------------------------------------------/
/  Configurations of FatFs Module
/---------------------------------------------------------------------------*/

#define FFCONF_DEF	5380	/* Revision ID */

/*---------------------------------------------------------------------------/
/ Function Configurations
/---------------------------------------------------------------------------*/

#define FF_FS_READONLY	0
/* 0: Read/Write - Cho phép c? d?c và ghi d? li?u */
#define FF_FS_MINIMIZE	0
/* 0: Gi? t?t c? ch?c nang co b?n (f_stat, f_getfree, f_unlink, v.v.) */
#define FF_USE_FIND		0
/* 0: Không c?n tìm ki?m file nâng cao */
#define FF_USE_MKFS		1
/* 1: B?t hàm f_mkfs() d? t? format th? SD thành FAT32 n?u c?n */
#define FF_USE_FASTSEEK	0
/* 0: Không dùng tính nang seek nhanh */
#define FF_USE_EXPAND	0
/* 0: Không dùng f_expand() */
#define FF_USE_CHMOD	0
/* 0: Không c?n thay d?i thu?c tính file */
#define FF_USE_LABEL	0
/* 0: Không c?n d?t tên volume */
#define FF_USE_FORWARD	0
/* 0: Không c?n chuy?n ti?p d? li?u */
#define FF_USE_STRFUNC	1
/* 1: H? tr? ghi chu?i (f_puts, f_printf) */
#define FF_PRINT_LLI	0
/* 0: Không c?n h? tr? long long trong f_printf */
#define FF_PRINT_FLOAT	0
/* 0: Không c?n h? tr? s? th?c trong f_printf */
#define FF_STRF_ENCODE	3
/* 3: Dùng UTF-8 cho chu?i (h? tr? ti?ng Vi?t t?t hon) */

/*---------------------------------------------------------------------------/
/ Locale and Namespace Configurations
/---------------------------------------------------------------------------*/

#define FF_CODE_PAGE	850
/* 850: Latin 1 - H? tr? t?t cho các ký t? châu Âu và Vi?t Nam */
/* Có th? d?i thành 437 (US) n?u không c?n ti?ng Vi?t */

#define FF_USE_LFN		0
/* 0: Không dùng tên file dài (Long File Name) d? ti?t ki?m tài nguyên */
#define FF_MAX_LFN		255
/* Gi? m?c d?nh 255 dù không dùng LFN */
#define FF_LFN_UNICODE	0
/* 0: Dùng ANSI/OEM, không c?n Unicode */
#define FF_LFN_BUF		255
#define FF_SFN_BUF		12
/* Kích thu?c buffer cho tên file ng?n */
#define FF_FS_RPATH		0
/* 0: Không c?n du?ng d?n tuong d?i */

/*---------------------------------------------------------------------------/
/ Drive/Volume Configurations
/---------------------------------------------------------------------------*/

#define FF_VOLUMES		1
/* 1: Ch? dùng 1 ? dia (1 SD Card) */
#define FF_STR_VOLUME_ID	0
/* 0: Không c?n d?nh danh chu?i cho volume */
#define FF_MULTI_PARTITION	0
/* 0: Không c?n h? tr? nhi?u phân vùng */
#define FF_MIN_SS		512
#define FF_MAX_SS		512
/* Sector size c? d?nh 512 byte - Phù h?p v?i SD Card */
#define FF_LBA64		0
/* 0: Không c?n h? tr? LBA 64-bit */
#define FF_MIN_GPT		0x10000000
/* Gi? m?c d?nh, không ?nh hu?ng vì FF_LBA64 = 0 */
#define FF_USE_TRIM		0
/* 0: Không c?n ATA-TRIM */

/*---------------------------------------------------------------------------/
/ System Configurations
/---------------------------------------------------------------------------*/

#define FF_FS_TINY		0
/* 0: Dùng buffer d?y d?, không t?i uu nh? g?n */
#define FF_FS_EXFAT		0
/* 0: Không h? tr? exFAT, ch? dùng FAT16/FAT32 */
#define FF_FS_NORTC		1
/* 1: Không có RTC, dùng th?i gian c? d?nh */
#define FF_NORTC_MON	3
#define FF_NORTC_MDAY	24
#define FF_NORTC_YEAR	2025
/* Th?i gian m?c d?nh: 24/03/2025 */
#define FF_FS_NOFSINFO	0
/* 0: Dùng thông tin FSINFO n?u có */
#define FF_FS_LOCK		0
/* 0: Không c?n khóa file */
#define FF_FS_REENTRANT	0
/* 0: Không c?n thread-safe */

/*--- End of configuration options ---*/
