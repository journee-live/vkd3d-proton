static const DWORD vs_no_attachments_code_dxbc[] =
{
    0x43425844, 0xcfb38ed1, 0xef3799fa, 0xf3032807, 0xf1c98b47, 0x00000001, 0x00000200, 0x00000004,
    0x00000030, 0x0000008c, 0x000000f4, 0x000001f0, 0x4e475349, 0x00000054, 0x00000002, 0x00000008,
    0x00000038, 0x00000000, 0x00000006, 0x00000001, 0x00000000, 0x00000101, 0x00000044, 0x00000000,
    0x00000008, 0x00000001, 0x00000001, 0x00000101, 0x565f5653, 0x65747265, 0x00444978, 0x495f5653,
    0x6174736e, 0x4965636e, 0xabab0044, 0x4e47534f, 0x00000060, 0x00000002, 0x00000008, 0x00000038,
    0x00000000, 0x00000001, 0x00000003, 0x00000000, 0x0000000f, 0x00000044, 0x00000000, 0x00000004,
    0x00000001, 0x00000001, 0x00000e01, 0x505f5653, 0x7469736f, 0x006e6f69, 0x525f5653, 0x65646e65,
    0x72615472, 0x41746567, 0x79617272, 0x65646e49, 0xabab0078, 0x58454853, 0x000000f4, 0x00010050,
    0x0000003d, 0x0100086a, 0x04000060, 0x00101012, 0x00000000, 0x00000006, 0x04000060, 0x00101012,
    0x00000001, 0x00000008, 0x04000067, 0x001020f2, 0x00000000, 0x00000001, 0x04000067, 0x00102012,
    0x00000001, 0x00000004, 0x02000068, 0x00000001, 0x07000020, 0x00100012, 0x00000000, 0x0010100a,
    0x00000000, 0x00004001, 0x00000001, 0x0f000037, 0x001000f2, 0x00000000, 0x00100006, 0x00000000,
    0x00004002, 0xbf800000, 0x40400000, 0x00000000, 0x3f800000, 0x00004002, 0x40400000, 0xbf800000,
    0x00000000, 0x3f800000, 0x0c000037, 0x001020f2, 0x00000000, 0x00101006, 0x00000000, 0x00100e46,
    0x00000000, 0x00004002, 0xbf800000, 0xbf800000, 0x00000000, 0x3f800000, 0x05000036, 0x00102012,
    0x00000001, 0x0010100a, 0x00000001, 0x0100003e, 0x30494653, 0x00000008, 0x00002000, 0x00000000,
};
#ifdef __GNUC__
#define UNUSED_ARRAY_ATTR __attribute__((unused))
#else
#define UNUSED_ARRAY_ATTR
#endif
UNUSED_ARRAY_ATTR static const D3D12_SHADER_BYTECODE vs_no_attachments_dxbc = { vs_no_attachments_code_dxbc, sizeof(vs_no_attachments_code_dxbc) };
#undef UNUSED_ARRAY_ATTR
