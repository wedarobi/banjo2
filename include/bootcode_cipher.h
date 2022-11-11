#ifndef __BOOTCODE_CIPHER_H__
#define __BOOTCODE_CIPHER_H__


/**
 * Bootcode cipher constants.
 */
#define BCCI_0000 (0x00000000) //! this one is invalid, but kept for consistency
#define BCCI_0001 (0x00000CC0)
#define BCCI_0002 (0x00000B74)
#define BCCI_0003 (0x00000CB8)
#define BCCI_0004 (0x00000B80)
#define BCCI_0005 (0x00000290)
#define BCCI_0006 (0x00000B14)
#define BCCI_0007 (0x0B140CC0)
#define BCCI_0008 (0x00000C68)
#define BCCI_0009 (0x00000280)
#define BCCI_000A (0x00000A68)
#define BCCI_000B (0x000009DA)
#define BCCI_000C (0x00000928)
#define BCCI_000D (0x00000CC8)
#define BCCI_000E (0x00000148)
#define BCCI_000F (0x00000004)
#define BCCI_0010 (0x00000B98)
#define BCCI_0011 (0x0000091A)
#define BCCI_0012 (0x000003EA)
#define BCCI_0013 (0x00000480)
#define BCCI_0014 (0x00000930)
#define BCCI_0015 (0x09300CC0)
#define BCCI_0016 (0x000002F4)
#define BCCI_0017 (0x02F40CC0)
#define BCCI_0018 (0x0000099C)
#define BCCI_0019 (0x00000AE0)
#define BCCI_001A (0x00000BAA)
#define BCCI_001B (0x00000C56)
#define BCCI_001C (0x00000C60)
#define BCCI_001D (0x0C600CC0)
#define BCCI_001E (0x0C600B74)
#define BCCI_001F (0x0000067C)
#define BCCI_0020 (0x00000BA4)
#define BCCI_0021 (0x0000034C)
#define BCCI_0022 (0x034C0CC0)
#define BCCI_0023 (0x034C0B74)
#define BCCI_0024 (0x00000940)
#define BCCI_0025 (0x09400CC0)
#define BCCI_0026 (0x09400B74)
#define BCCI_0027 (0x00000AD4)
#define BCCI_0028 (0x00000C64)
#define BCCI_0029 (0x0C640CC0)
#define BCCI_002A (0x0C640B74)
#define BCCI_002B (0x0C640CB8)
#define BCCI_002C (0x00000948)
#define BCCI_002D (0x09480CC0)
#define BCCI_002E (0x09480B74)
#define BCCI_002F (0x09480CB8)
#define BCCI_0030 (0x0000094C)
#define BCCI_0031 (0x094C0CC0)
#define BCCI_0032 (0x094C0B74)
#define BCCI_0033 (0x094C0CB8)
#define BCCI_0034 (0x00000950)
#define BCCI_0035 (0x09500CC0)
#define BCCI_0036 (0x09500B74)
#define BCCI_0037 (0x09500CB8)
#define BCCI_0038 (0x00000954)
#define BCCI_0039 (0x09540CC0)
#define BCCI_003A (0x09540B74)
#define BCCI_003B (0x09540CB8)
#define BCCI_003C (0x00000958)
#define BCCI_003D (0x09580CC0)
#define BCCI_003E (0x09580B74)
#define BCCI_003F (0x00000B50)
#define BCCI_0040 (0x00000C8C)
#define BCCI_0041 (0x00000B20)
#define BCCI_0042 (0x0B200CC0)
#define BCCI_0043 (0x0B200B74)
#define BCCI_0044 (0x0000091C)
#define BCCI_0045 (0x091C0CC0)
#define BCCI_0046 (0x091C0B74)
#define BCCI_0047 (0x091C0CB8)
#define BCCI_0048 (0x00000960)
#define BCCI_0049 (0x000009B6)
#define BCCI_004A (0x09B60CC0)
#define BCCI_004B (0x09B60B74)
#define BCCI_004C (0x00000964)
#define BCCI_004D (0x09640CC0)
#define BCCI_004E (0x00000038)
#define BCCI_004F (0x000006C2)
#define BCCI_0050 (0x000009CC)
#define BCCI_0051 (0x09CC0CC0)
#define BCCI_0052 (0x09CC0B74)
#define BCCI_0053 (0x09CC0CB8)
#define BCCI_0054 (0x0000096C)
#define BCCI_0055 (0x096C0CC0)
#define BCCI_0056 (0x096C0B74)
#define BCCI_0057 (0x096C0CB8)
#define BCCI_0058 (0x00000970)
#define BCCI_0059 (0x09700CC0)
#define BCCI_005A (0x09700B74)
#define BCCI_005B (0x09700CB8)
#define BCCI_005C (0x00000974)
#define BCCI_005D (0x09740CC0)
#define BCCI_005E (0x09740B74)
#define BCCI_005F (0x09740CB8)
#define BCCI_0060 (0x00000978)
#define BCCI_0061 (0x09780CC0)
#define BCCI_0062 (0x0000068A)
#define BCCI_0063 (0x068A0CC0)
#define BCCI_0064 (0x00000914)
#define BCCI_0065 (0x09140CC0)
#define BCCI_0066 (0x09140B74)
#define BCCI_0067 (0x00000DAE)
#define BCCI_0068 (0x0DAE0CC0)
#define BCCI_0069 (0x0DAE0B74)
#define BCCI_006A (0x0DAE0CB8)
#define BCCI_006B (0x0DAE0B80)
#define BCCI_006C (0x0DAE0290)
#define BCCI_006D (0x000003DA)
#define BCCI_006E (0x03DA0CC0)
#define BCCI_006F (0x03DA0B74)
#define BCCI_0070 (0x03DA0CB8)
#define BCCI_0071 (0x03DA0B80)
#define BCCI_0072 (0x03DA0290)
#define BCCI_0073 (0x03DA0B14)
#define BCCI_0074 (0x0DAE0CC8)
#define BCCI_0075 (0x03DA0C68)
#define BCCI_0076 (0x03DA0280)
#define BCCI_0077 (0x03DA0A68)
#define BCCI_0078 (0x03DA09DA)
#define BCCI_0079 (0x03DA0928)
#define BCCI_007A (0x03DA0CC8)
#define BCCI_007B (0x03DA0148)
#define BCCI_007C (0x03DA0004)
#define BCCI_007D (0x03DA0B98)
#define BCCI_007E (0x03DA091A)
#define BCCI_007F (0x03DA03EA)
#define BCCI_0080 (0x00000C4C)
#define BCCI_0081 (0x0C4C0CC0)
#define BCCI_0082 (0x0C4C0B74)
#define BCCI_0083 (0x0C4C0CB8)
#define BCCI_0084 (0x0C4C0B80)
#define BCCI_0085 (0x0C4C0290)
#define BCCI_0086 (0x0C4C0B14)
#define BCCI_0087 (0x03DA0BAA)
#define BCCI_0088 (0x00000AF6)
#define BCCI_0089 (0x0AF60CC0)
#define BCCI_008A (0x0AF60B74)
#define BCCI_008B (0x000009E6)
#define BCCI_008C (0x09E60CC0)
#define BCCI_008D (0x09E60B74)
#define BCCI_008E (0x09E60CB8)
#define BCCI_008F (0x09E60B80)
#define BCCI_0090 (0x09E60290)
#define BCCI_0091 (0x09E60B14)
#define BCCI_0092 (0x0AF60A68)
#define BCCI_0093 (0x09E60C68)
#define BCCI_0094 (0x09E60280)
#define BCCI_0095 (0x09E60A68)
#define BCCI_0096 (0x09E609DA)
#define BCCI_0097 (0x09E60928)
#define BCCI_0098 (0x09E60CC8)
#define BCCI_0099 (0x09E60148)
#define BCCI_009A (0x09E60004)
#define BCCI_009B (0x09E60B98)
#define BCCI_009C (0x09E6091A)
#define BCCI_009D (0x09E603EA)
#define BCCI_009E (0x09E60480)
#define BCCI_009F (0x09E60930)
#define BCCI_00A0 (0x00000980)
#define BCCI_00A1 (0x0000061A)
#define BCCI_00A2 (0x061A0CC0)
#define BCCI_00A3 (0x061A0B74)
#define BCCI_00A4 (0x061A0CB8)
#define BCCI_00A5 (0x061A0B80)
#define BCCI_00A6 (0x061A0290)
#define BCCI_00A7 (0x061A0B14)
#define BCCI_00A8 (0x09800C68)
#define BCCI_00A9 (0x061A0C68)
#define BCCI_00AA (0x000006E4)
#define BCCI_00AB (0x06E40CC0)
#define BCCI_00AC (0x06E40B74)
#define BCCI_00AD (0x00000540)
#define BCCI_00AE (0x05400CC0)
#define BCCI_00AF (0x05400B74)
#define BCCI_00B0 (0x05400CB8)
#define BCCI_00B1 (0x05400B80)
#define BCCI_00B2 (0x05400290)
#define BCCI_00B3 (0x05400B14)
#define BCCI_00B4 (0x06E40A68)
#define BCCI_00B5 (0x05400C68)
#define BCCI_00B6 (0x05400280)
#define BCCI_00B7 (0x05400A68)
#define BCCI_00B8 (0x054009DA)
#define BCCI_00B9 (0x05400928)
#define BCCI_00BA (0x05400CC8)
#define BCCI_00BB (0x05400148)
#define BCCI_00BC (0x05400004)
#define BCCI_00BD (0x05400B98)
#define BCCI_00BE (0x0540091A)
#define BCCI_00BF (0x054003EA)
#define BCCI_00C0 (0x05400480)
#define BCCI_00C1 (0x05400930)
#define BCCI_00C2 (0x00000692)
#define BCCI_00C3 (0x06920CC0)
#define BCCI_00C4 (0x000006B2)
#define BCCI_00C5 (0x06B20CC0)
#define BCCI_00C6 (0x06B20B74)
#define BCCI_00C7 (0x06B20CB8)
#define BCCI_00C8 (0x06B20B80)
#define BCCI_00C9 (0x06B20290)
#define BCCI_00CA (0x06B20B14)
#define BCCI_00CB (0x06920280)
#define BCCI_00CC (0x06B20C68)
#define BCCI_00CD (0x06B20280)
#define BCCI_00CE (0x000004D0)
#define BCCI_00CF (0x04D00CC0)
#define BCCI_00D0 (0x000003CA)
#define BCCI_00D1 (0x03CA0CC0)
#define BCCI_00D2 (0x03CA0B74)
#define BCCI_00D3 (0x03CA0CB8)
#define BCCI_00D4 (0x03CA0B80)
#define BCCI_00D5 (0x03CA0290)
#define BCCI_00D6 (0x03CA0B14)
#define BCCI_00D7 (0x04D00280)
#define BCCI_00D8 (0x03CA0C68)
#define BCCI_00D9 (0x03CA0280)
#define BCCI_00DA (0x03CA0A68)
#define BCCI_00DB (0x03CA09DA)
#define BCCI_00DC (0x03CA0928)
#define BCCI_00DD (0x03CA0CC8)
#define BCCI_00DE (0x03CA0148)
#define BCCI_00DF (0x03CA0004)
#define BCCI_00E0 (0x03CA0B98)
#define BCCI_00E1 (0x03CA091A)
#define BCCI_00E2 (0x000006A6)
#define BCCI_00E3 (0x06A60CC0)
#define BCCI_00E4 (0x06A60B74)
#define BCCI_00E5 (0x06A60CB8)
#define BCCI_00E6 (0x06A60B80)
#define BCCI_00E7 (0x06A60290)
#define BCCI_00E8 (0x000003D2)
#define BCCI_00E9 (0x03D20CC0)
#define BCCI_00EA (0x000006DE)
#define BCCI_00EB (0x06DE0CC0)
#define BCCI_00EC (0x06DE0B74)
#define BCCI_00ED (0x000000D0)
#define BCCI_00EE (0x00D00CC0)
#define BCCI_00EF (0x00D00B74)
#define BCCI_00F0 (0x0000076C)
#define BCCI_00F1 (0x076C0CC0)
#define BCCI_00F2 (0x076C0B74)
#define BCCI_00F3 (0x076C0CB8)
#define BCCI_00F4 (0x076C0B80)
#define BCCI_00F5 (0x076C0290)
#define BCCI_00F6 (0x076C0B14)
#define BCCI_00F7 (0x00D00A68)
#define BCCI_00F8 (0x076C0C68)
#define BCCI_00F9 (0x076C0280)
#define BCCI_00FA (0x076C0A68)
#define BCCI_00FB (0x076C09DA)
#define BCCI_00FC (0x076C0928)
#define BCCI_00FD (0x076C0CC8)
#define BCCI_00FE (0x076C0148)
#define BCCI_00FF (0x00000B48)
#define BCCI_0100 (0x00000288)
#define BCCI_0101 (0x000001BC)
#define BCCI_0102 (0x01BC0CC0)
#define BCCI_0103 (0x01BC0B74)
#define BCCI_0104 (0x00000B12)
#define BCCI_0105 (0x0B120CC0)
#define BCCI_0106 (0x0B120B74)
#define BCCI_0107 (0x000003B6)
#define BCCI_0108 (0x03B60CC0)
#define BCCI_0109 (0x00000506)
#define BCCI_010A (0x0000058E)
#define BCCI_010B (0x0000058A)
#define BCCI_010C (0x058A0CC0)
#define BCCI_010D (0x058A0B74)
#define BCCI_010E (0x058A0CB8)
#define BCCI_010F (0x0000015C)
#define BCCI_0110 (0x015C0CC0)
#define BCCI_0111 (0x015C0B74)
#define BCCI_0112 (0x015C0CB8)
#define BCCI_0113 (0x015C0B80)
#define BCCI_0114 (0x015C0290)
#define BCCI_0115 (0x015C0B14)
#define BCCI_0116 (0x00000332)
#define BCCI_0117 (0x03320CC0)
#define BCCI_0118 (0x03320B74)
#define BCCI_0119 (0x03320CB8)
#define BCCI_011A (0x03320B80)
#define BCCI_011B (0x00000D84)
#define BCCI_011C (0x00000EE4)
#define BCCI_011D (0x0EE40CC0)
#define BCCI_011E (0x0EE40B74)
#define BCCI_011F (0x0EE40CB8)
#define BCCI_0120 (0x000007CE)
#define BCCI_0121 (0x07CE0CC0)
#define BCCI_0122 (0x07CE0B74)
#define BCCI_0123 (0x07CE0CB8)
#define BCCI_0124 (0x07CE0B80)
#define BCCI_0125 (0x07CE0290)
#define BCCI_0126 (0x07CE0B14)
#define BCCI_0127 (0x0EE409DA)
#define BCCI_0128 (0x07CE0C68)
#define BCCI_0129 (0x07CE0280)
#define BCCI_012A (0x0000056A)
#define BCCI_012B (0x056A0CC0)
#define BCCI_012C (0x056A0B74)
#define BCCI_012D (0x056A0CB8)
#define BCCI_012E (0x056A0B80)
#define BCCI_012F (0x056A0290)
#define BCCI_0130 (0x056A0B14)
#define BCCI_0131 (0x07CE091A)
#define BCCI_0132 (0x000003F6)
#define BCCI_0133 (0x03F60CC0)
#define BCCI_0134 (0x03F60B74)
#define BCCI_0135 (0x03F60CB8)
#define BCCI_0136 (0x00000E92)
#define BCCI_0137 (0x0E920CC0)
#define BCCI_0138 (0x00000E34)
#define BCCI_0139 (0x0E340CC0)
#define BCCI_013A (0x0E340B74)
#define BCCI_013B (0x0E340CB8)
#define BCCI_013C (0x0E340B80)
#define BCCI_013D (0x0E340290)
#define BCCI_013E (0x0E340B14)
#define BCCI_013F (0x0E920280)
#define BCCI_0140 (0x0E340C68)
#define BCCI_0141 (0x0E340280)
#define BCCI_0142 (0x0E340A68)
#define BCCI_0143 (0x0E3409DA)
#define BCCI_0144 (0x0E340928)
#define BCCI_0145 (0x0E340CC8)
#define BCCI_0146 (0x0E340148)
#define BCCI_0147 (0x0E340004)
#define BCCI_0148 (0x0000004E)
#define BCCI_0149 (0x004E0CC0)
#define BCCI_014A (0x004E0B74)
#define BCCI_014B (0x000004EE)
#define BCCI_014C (0x04EE0CC0)
#define BCCI_014D (0x04EE0B74)
#define BCCI_014E (0x00000B2E)
#define BCCI_014F (0x0B2E0CC0)
#define BCCI_0150 (0x0B2E0B74)
#define BCCI_0151 (0x0B2E0CB8)
#define BCCI_0152 (0x0B2E0B80)
#define BCCI_0153 (0x0B2E0290)
#define BCCI_0154 (0x0B2E0B14)
#define BCCI_0155 (0x04EE0A68)
#define BCCI_0156 (0x0B2E0C68)
#define BCCI_0157 (0x0B2E0280)
#define BCCI_0158 (0x0B2E0A68)
#define BCCI_0159 (0x0B2E09DA)
#define BCCI_015A (0x0B2E0928)
#define BCCI_015B (0x0B2E0CC8)
#define BCCI_015C (0x0B2E0148)
#define BCCI_015D (0x0B2E0004)
#define BCCI_015E (0x0B2E0B98)
#define BCCI_015F (0x0B2E091A)
#define BCCI_0160 (0x000000B2)
#define BCCI_0161 (0x00B20CC0)
#define BCCI_0162 (0x0000069A)
#define BCCI_0163 (0x069A0CC0)
#define BCCI_0164 (0x069A0B74)
#define BCCI_0165 (0x069A0CB8)
#define BCCI_0166 (0x069A0B80)
#define BCCI_0167 (0x069A0290)
#define BCCI_0168 (0x0000020E)
#define BCCI_0169 (0x0000050A)
#define BCCI_016A (0x0000051E)
#define BCCI_016B (0x051E0CC0)
#define BCCI_016C (0x051E0B74)
#define BCCI_016D (0x051E0CB8)
#define BCCI_016E (0x051E0B80)
#define BCCI_016F (0x051E0290)
#define BCCI_0170 (0x051E0B14)
#define BCCI_0171 (0x050A0C68)
#define BCCI_0172 (0x051E0C68)
#define BCCI_0173 (0x051E0280)
#define BCCI_0174 (0x051E0A68)
#define BCCI_0175 (0x051E09DA)
#define BCCI_0176 (0x051E0928)
#define BCCI_0177 (0x051E0CC8)
#define BCCI_0178 (0x051E0148)
#define BCCI_0179 (0x051E0004)
#define BCCI_017A (0x000009C6)
#define BCCI_017B (0x09C60CC0)
#define BCCI_017C (0x09C60B74)
#define BCCI_017D (0x09C60CB8)
#define BCCI_017E (0x09C60B80)
#define BCCI_017F (0x09C60290)
#define BCCI_0180 (0x000009AA)
#define BCCI_0181 (0x09AA0CC0)
#define BCCI_0182 (0x09AA0B74)
#define BCCI_0183 (0x09AA0CB8)
#define BCCI_0184 (0x09AA0B80)
#define BCCI_0185 (0x09AA0290)
#define BCCI_0186 (0x09AA0B14)
#define BCCI_0187 (0x09C60CC8)
#define BCCI_0188 (0x09AA0C68)
#define BCCI_0189 (0x09AA0280)
#define BCCI_018A (0x09AA0A68)
#define BCCI_018B (0x09AA09DA)
#define BCCI_018C (0x09AA0928)
#define BCCI_018D (0x09AA0CC8)
#define BCCI_018E (0x09AA0148)
#define BCCI_018F (0x09AA0004)
#define BCCI_0190 (0x09AA0B98)
#define BCCI_0191 (0x09AA091A)
#define BCCI_0192 (0x09AA03EA)
#define BCCI_0193 (0x09AA0480)
#define BCCI_0194 (0x09AA0930)
#define BCCI_0195 (0x09C60C56)
#define BCCI_0196 (0x09AA02F4)
#define BCCI_0197 (0x0B2E09B6)
#define BCCI_0198 (0x09AA099C)
#define BCCI_0199 (0x09AA0AE0)
#define BCCI_019A (0x09AA0BAA)
#define BCCI_019B (0x09AA0C56)
#define BCCI_019C (0x09AA0C60)
#define BCCI_019D (0x050A0950)
#define BCCI_019E (0x09C60940)
#define BCCI_019F (0x09AA067C)
#define BCCI_01A0 (0x09AA0BA4)
#define BCCI_01A1 (0x09AA034C)
#define BCCI_01A2 (0x09C60C64)
#define BCCI_01A3 (0x00000682)
#define BCCI_01A4 (0x06820CC0)
#define BCCI_01A5 (0x06820B74)
#define BCCI_01A6 (0x06820CB8)
#define BCCI_01A7 (0x06820B80)
#define BCCI_01A8 (0x06820290)
#define BCCI_01A9 (0x06820B14)
#define BCCI_01AA (0x09C6094C)
#define BCCI_01AB (0x06820C68)
#define BCCI_01AC (0x06820280)
#define BCCI_01AD (0x06820A68)
#define BCCI_01AE (0x068209DA)
#define BCCI_01AF (0x06820928)
#define BCCI_01B0 (0x06820CC8)
#define BCCI_01B1 (0x06820148)
#define BCCI_01B2 (0x06820004)
#define BCCI_01B3 (0x06820B98)
#define BCCI_01B4 (0x0682091A)
#define BCCI_01B5 (0x068203EA)
#define BCCI_01B6 (0x06820480)
#define BCCI_01B7 (0x06820930)
#define BCCI_01B8 (0x09AA0954)
#define BCCI_01B9 (0x068202F4)
#define BCCI_01BA (0x09C60C8C)
#define BCCI_01BB (0x0682099C)
#define BCCI_01BC (0x06820AE0)
#define BCCI_01BD (0x06820BAA)
#define BCCI_01BE (0x06820C56)
#define BCCI_01BF (0x06820C60)
#define BCCI_01C0 (0x00000B0A)
#define BCCI_01C1 (0x0B0A0CC0)
#define BCCI_01C2 (0x0B0A0B74)
#define BCCI_01C3 (0x0B0A0CB8)
#define BCCI_01C4 (0x0B0A0B80)
#define BCCI_01C5 (0x0B0A0290)
#define BCCI_01C6 (0x0B0A0B14)
#define BCCI_01C7 (0x06820940)
#define BCCI_01C8 (0x0000033E)
#define BCCI_01C9 (0x033E0CC0)
#define BCCI_01CA (0x033E0B74)
#define BCCI_01CB (0x000006E2)
#define BCCI_01CC (0x06E20CC0)
#define BCCI_01CD (0x06E20B74)
#define BCCI_01CE (0x06E20CB8)
#define BCCI_01CF (0x06E20B80)
#define BCCI_01D0 (0x06E20290)
#define BCCI_01D1 (0x06E20B14)
#define BCCI_01D2 (0x033E0A68)
#define BCCI_01D3 (0x06E20C68)
#define BCCI_01D4 (0x06E20280)
#define BCCI_01D5 (0x06E20A68)
#define BCCI_01D6 (0x06E209DA)
#define BCCI_01D7 (0x06E20928)
#define BCCI_01D8 (0x0000068E)
#define BCCI_01D9 (0x068E0CC0)
#define BCCI_01DA (0x00000E48)
#define BCCI_01DB (0x0E480CC0)
#define BCCI_01DC (0x0E480B74)
#define BCCI_01DD (0x0E480CB8)
#define BCCI_01DE (0x0E480B80)
#define BCCI_01DF (0x0E480290)
#define BCCI_01E0 (0x0E480B14)
#define BCCI_01E1 (0x068E0280)
#define BCCI_01E2 (0x00000686)
#define BCCI_01E3 (0x06860CC0)
#define BCCI_01E4 (0x06860B74)
#define BCCI_01E5 (0x06860CB8)
#define BCCI_01E6 (0x06860B80)
#define BCCI_01E7 (0x06860290)
#define BCCI_01E8 (0x06860B14)
#define BCCI_01E9 (0x0E480004)
#define BCCI_01EA (0x06860C68)
#define BCCI_01EB (0x06860280)
#define BCCI_01EC (0x000006C6)
#define BCCI_01ED (0x06C60CC0)
#define BCCI_01EE (0x06C60B74)
#define BCCI_01EF (0x06C60CB8)
#define BCCI_01F0 (0x000002C2)
#define BCCI_01F1 (0x02C20CC0)
#define BCCI_01F2 (0x02C20B74)
#define BCCI_01F3 (0x02C20CB8)
#define BCCI_01F4 (0x02C20B80)
#define BCCI_01F5 (0x02C20290)
#define BCCI_01F6 (0x02C20B14)
#define BCCI_01F7 (0x06C609DA)
#define BCCI_01F8 (0x02C20C68)
#define BCCI_01F9 (0x02C20280)
#define BCCI_01FA (0x00000BAE)
#define BCCI_01FB (0x0BAE0CC0)
#define BCCI_01FC (0x0BAE0B74)
#define BCCI_01FD (0x0BAE0CB8)
#define BCCI_01FE (0x0BAE0B80)
#define BCCI_01FF (0x0BAE0290)
#define BCCI_0200 (0x0000062C)
#define BCCI_0201 (0x062C0CC0)
#define BCCI_0202 (0x062C0B74)
#define BCCI_0203 (0x062C0CB8)
#define BCCI_0204 (0x000006A2)
#define BCCI_0205 (0x06A20CC0)
#define BCCI_0206 (0x00000732)
#define BCCI_0207 (0x07320CC0)
#define BCCI_0208 (0x07320B74)
#define BCCI_0209 (0x07320CB8)
#define BCCI_020A (0x07320B80)
#define BCCI_020B (0x07320290)
#define BCCI_020C (0x07320B14)
#define BCCI_020D (0x06A20280)
#define BCCI_020E (0x07320C68)
#define BCCI_020F (0x07320280)
#define BCCI_0210 (0x07320A68)
#define BCCI_0211 (0x073209DA)
#define BCCI_0212 (0x07320928)
#define BCCI_0213 (0x07320CC8)
#define BCCI_0214 (0x07320148)
#define BCCI_0215 (0x07320004)
#define BCCI_0216 (0x07320B98)
#define BCCI_0217 (0x0732091A)
#define BCCI_0218 (0x073203EA)
#define BCCI_0219 (0x07320480)
#define BCCI_021A (0x07320930)
#define BCCI_021B (0x062C0C56)
#define BCCI_021C (0x073202F4)
#define BCCI_021D (0x06A20AE0)
#define BCCI_021E (0x0732099C)
#define BCCI_021F (0x000001E8)
#define BCCI_0220 (0x01E80CC0)
#define BCCI_0221 (0x01E80B74)
#define BCCI_0222 (0x00000906)
#define BCCI_0223 (0x09060CC0)
#define BCCI_0224 (0x09060B74)
#define BCCI_0225 (0x09060CB8)
#define BCCI_0226 (0x09060B80)
#define BCCI_0227 (0x09060290)
#define BCCI_0228 (0x09060B14)
#define BCCI_0229 (0x01E80A68)
#define BCCI_022A (0x09060C68)
#define BCCI_022B (0x09060280)
#define BCCI_022C (0x09060A68)
#define BCCI_022D (0x090609DA)
#define BCCI_022E (0x09060928)
#define BCCI_022F (0x09060CC8)
#define BCCI_0230 (0x09060148)
#define BCCI_0231 (0x09060004)
#define BCCI_0232 (0x09060B98)
#define BCCI_0233 (0x00000E50)
#define BCCI_0234 (0x0E500CC0)
#define BCCI_0235 (0x0E500B74)
#define BCCI_0236 (0x0E500CB8)
#define BCCI_0237 (0x0E500B80)
#define BCCI_0238 (0x0E500290)
#define BCCI_0239 (0x0E500B14)
#define BCCI_023A (0x0906099C)
#define BCCI_023B (0x0E500C68)
#define BCCI_023C (0x0E500280)
#define BCCI_023D (0x0E500A68)
#define BCCI_023E (0x0E5009DA)
#define BCCI_023F (0x0E500928)
#define BCCI_0240 (0x00000CA8)
#define BCCI_0241 (0x0CA80CC0)
#define BCCI_0242 (0x0CA80B74)
#define BCCI_0243 (0x0CA80CB8)
#define BCCI_0244 (0x0CA80B80)
#define BCCI_0245 (0x0CA80290)
#define BCCI_0246 (0x0CA80B14)
#define BCCI_0247 (0x0E500930)
#define BCCI_0248 (0x0CA80C68)
#define BCCI_0249 (0x0CA80280)
#define BCCI_024A (0x0CA80A68)
#define BCCI_024B (0x0CA809DA)
#define BCCI_024C (0x0CA80928)
#define BCCI_024D (0x0CA80CC8)
#define BCCI_024E (0x0CA80148)
#define BCCI_024F (0x0CA80004)
#define BCCI_0250 (0x0CA80B98)
#define BCCI_0251 (0x0CA8091A)
#define BCCI_0252 (0x0CA803EA)
#define BCCI_0253 (0x0CA80480)
#define BCCI_0254 (0x0CA80930)
#define BCCI_0255 (0x073206C2)
#define BCCI_0256 (0x0CA802F4)
#define BCCI_0257 (0x0E500940)
#define BCCI_0258 (0x0CA8099C)
#define BCCI_0259 (0x0CA80AE0)
#define BCCI_025A (0x0CA80BAA)
#define BCCI_025B (0x0CA80C56)
#define BCCI_025C (0x0CA80C60)
#define BCCI_025D (0x02C203DA)
#define BCCI_025E (0x09060958)
#define BCCI_025F (0x0CA8067C)
#define BCCI_0260 (0x0CA80BA4)
#define BCCI_0261 (0x000008F0)
#define BCCI_0262 (0x08F00CC0)
#define BCCI_0263 (0x08F00B74)
#define BCCI_0264 (0x08F00CB8)
#define BCCI_0265 (0x08F00B80)
#define BCCI_0266 (0x08F00290)
#define BCCI_0267 (0x08F00B14)
#define BCCI_0268 (0x0CA80C64)
#define BCCI_0269 (0x08F00C68)
#define BCCI_026A (0x08F00280)
#define BCCI_026B (0x08F00A68)
#define BCCI_026C (0x08F009DA)
#define BCCI_026D (0x08F00928)
#define BCCI_026E (0x08F00CC8)
#define BCCI_026F (0x08F00148)
#define BCCI_0270 (0x08F00004)
#define BCCI_0271 (0x08F00B98)
#define BCCI_0272 (0x08F0091A)
#define BCCI_0273 (0x08F003EA)
#define BCCI_0274 (0x08F00480)
#define BCCI_0275 (0x08F00930)
#define BCCI_0276 (0x0906096C)
#define BCCI_0277 (0x08F002F4)
#define BCCI_0278 (0x0CA80954)
#define BCCI_0279 (0x00000D20)
#define BCCI_027A (0x0D200CC0)
#define BCCI_027B (0x0D200B74)
#define BCCI_027C (0x0D200CB8)
#define BCCI_027D (0x0D200B80)
#define BCCI_027E (0x0D200290)
#define BCCI_027F (0x0D200B14)
#define BCCI_0280 (0x08F0067C)
#define BCCI_0281 (0x0D200C68)
#define BCCI_0282 (0x0D200280)
#define BCCI_0283 (0x0D200A68)
#define BCCI_0284 (0x000009A4)
#define BCCI_0285 (0x09A40CC0)
#define BCCI_0286 (0x09A40B74)
#define BCCI_0287 (0x09A40CB8)
#define BCCI_0288 (0x0000025E)
#define BCCI_0289 (0x025E0CC0)
#define BCCI_028A (0x025E0B74)
#define BCCI_028B (0x025E0CB8)
#define BCCI_028C (0x025E0B80)
#define BCCI_028D (0x025E0290)
#define BCCI_028E (0x025E0B14)
#define BCCI_028F (0x09A409DA)
#define BCCI_0290 (0x025E0C68)
#define BCCI_0291 (0x025E0280)
#define BCCI_0292 (0x025E0A68)
#define BCCI_0293 (0x025E09DA)
#define BCCI_0294 (0x025E0928)
#define BCCI_0295 (0x025E0CC8)
#define BCCI_0296 (0x025E0148)
#define BCCI_0297 (0x025E0004)
#define BCCI_0298 (0x025E0B98)
#define BCCI_0299 (0x025E091A)
#define BCCI_029A (0x025E03EA)
#define BCCI_029B (0x025E0480)
#define BCCI_029C (0x025E0930)
#define BCCI_029D (0x09A40AE0)
#define BCCI_029E (0x025E02F4)
#define BCCI_029F (0x09A40C56)
#define BCCI_02A0 (0x025E099C)
#define BCCI_02A1 (0x000009EC)
#define BCCI_02A2 (0x09EC0CC0)
#define BCCI_02A3 (0x09EC0B74)
#define BCCI_02A4 (0x09EC0CB8)
#define BCCI_02A5 (0x09EC0B80)
#define BCCI_02A6 (0x09EC0290)
#define BCCI_02A7 (0x09EC0B14)
#define BCCI_02A8 (0x025E0BA4)
#define BCCI_02A9 (0x09EC0C68)
#define BCCI_02AA (0x09EC0280)
#define BCCI_02AB (0x09EC0A68)
#define BCCI_02AC (0x09EC09DA)
#define BCCI_02AD (0x09EC0928)
#define BCCI_02AE (0x09EC0CC8)
#define BCCI_02AF (0x09EC0148)
#define BCCI_02B0 (0x09EC0004)
#define BCCI_02B1 (0x09EC0B98)
#define BCCI_02B2 (0x09EC091A)
#define BCCI_02B3 (0x09EC03EA)
#define BCCI_02B4 (0x09EC0480)
#define BCCI_02B5 (0x09EC0930)
#define BCCI_02B6 (0x09AA0E92)
#define BCCI_02B7 (0x09EC02F4)
#define BCCI_02B8 (0x025E094C)
#define BCCI_02B9 (0x09EC099C)
#define BCCI_02BA (0x09EC0AE0)
#define BCCI_02BB (0x09EC0BAA)
#define BCCI_02BC (0x09EC0C56)
#define BCCI_02BD (0x09EC0C60)
#define BCCI_02BE (0x0E5009E6)
#define BCCI_02BF (0x01E80980)
#define BCCI_02C0 (0x0000060E)
#define BCCI_02C1 (0x060E0CC0)
#define BCCI_02C2 (0x060E0B74)
#define BCCI_02C3 (0x060E0CB8)
#define BCCI_02C4 (0x060E0B80)
#define BCCI_02C5 (0x060E0290)
#define BCCI_02C6 (0x060E0B14)
#define BCCI_02C7 (0x025E0B50)
#define BCCI_02C8 (0x0000034A)
#define BCCI_02C9 (0x00000412)
#define BCCI_02CA (0x04120CC0)
#define BCCI_02CB (0x04120B74)
#define BCCI_02CC (0x04120CB8)
#define BCCI_02CD (0x04120B80)
#define BCCI_02CE (0x04120290)
#define BCCI_02CF (0x000006DA)
#define BCCI_02D0 (0x06DA0CC0)
#define BCCI_02D1 (0x00000ABC)
#define BCCI_02D2 (0x0ABC0CC0)
#define BCCI_02D3 (0x0ABC0B74)
#define BCCI_02D4 (0x0ABC0CB8)
#define BCCI_02D5 (0x0ABC0B80)
#define BCCI_02D6 (0x0ABC0290)
#define BCCI_02D7 (0x0ABC0B14)
#define BCCI_02D8 (0x06DA0280)
#define BCCI_02D9 (0x0ABC0C68)
#define BCCI_02DA (0x0ABC0280)
#define BCCI_02DB (0x0ABC0A68)
#define BCCI_02DC (0x0ABC09DA)
#define BCCI_02DD (0x0ABC0928)
#define BCCI_02DE (0x0ABC0CC8)
#define BCCI_02DF (0x0ABC0148)
#define BCCI_02E0 (0x0ABC0004)
#define BCCI_02E1 (0x0ABC0B98)
#define BCCI_02E2 (0x0ABC091A)
#define BCCI_02E3 (0x0ABC03EA)
#define BCCI_02E4 (0x0ABC0480)
#define BCCI_02E5 (0x0ABC0930)
#define BCCI_02E6 (0x09A4068A)
#define BCCI_02E7 (0x0ABC02F4)
#define BCCI_02E8 (0x000003C2)
#define BCCI_02E9 (0x03C20CC0)
#define BCCI_02EA (0x03C20B74)
#define BCCI_02EB (0x03C20CB8)
#define BCCI_02EC (0x03C20B80)
#define BCCI_02ED (0x03C20290)
#define BCCI_02EE (0x03C20B14)
#define BCCI_02EF (0x06DA0BA4)
#define BCCI_02F0 (0x03C20C68)
#define BCCI_02F1 (0x03C20280)
#define BCCI_02F2 (0x03C20A68)
#define BCCI_02F3 (0x000000B6)
#define BCCI_02F4 (0x00B60CC0)
#define BCCI_02F5 (0x00000ACC)
#define BCCI_02F6 (0x0ACC0CC0)
#define BCCI_02F7 (0x00000E1A)
#define BCCI_02F8 (0x0E1A0CC0)
#define BCCI_02F9 (0x0E1A0B74)
#define BCCI_02FA (0x0E1A0CB8)
#define BCCI_02FB (0x0E1A0B80)
#define BCCI_02FC (0x0E1A0290)
#define BCCI_02FD (0x0E1A0B14)
#define BCCI_02FE (0x0ACC0280)
#define BCCI_02FF (0x000006CC)
#define BCCI_0300 (0x0000072C)
#define BCCI_0301 (0x072C0CC0)
#define BCCI_0302 (0x072C0B74)
#define BCCI_0303 (0x072C0CB8)
#define BCCI_0304 (0x072C0B80)
#define BCCI_0305 (0x072C0290)
#define BCCI_0306 (0x072C0B14)
#define BCCI_0307 (0x06CC0C68)
#define BCCI_0308 (0x00000232)
#define BCCI_0309 (0x02320CC0)
#define BCCI_030A (0x02320B74)
#define BCCI_030B (0x02320CB8)
#define BCCI_030C (0x0000073A)
#define BCCI_030D (0x073A0CC0)
#define BCCI_030E (0x073A0B74)
#define BCCI_030F (0x073A0CB8)
#define BCCI_0310 (0x073A0B80)
#define BCCI_0311 (0x073A0290)
#define BCCI_0312 (0x00000E60)
#define BCCI_0313 (0x0E600CC0)
#define BCCI_0314 (0x0E600B74)
#define BCCI_0315 (0x0E600CB8)
#define BCCI_0316 (0x0E600B80)
#define BCCI_0317 (0x0E600290)
#define BCCI_0318 (0x0E600B14)
#define BCCI_0319 (0x073A0CC8)
#define BCCI_031A (0x0E600C68)
#define BCCI_031B (0x0E600280)
#define BCCI_031C (0x0E600A68)
#define BCCI_031D (0x0E6009DA)
#define BCCI_031E (0x0E600928)
#define BCCI_031F (0x0E600CC8)
#define BCCI_0320 (0x00000AD8)
#define BCCI_0321 (0x0AD80CC0)
#define BCCI_0322 (0x0AD80B74)
#define BCCI_0323 (0x0AD80CB8)
#define BCCI_0324 (0x0AD80B80)
#define BCCI_0325 (0x0AD80290)
#define BCCI_0326 (0x000006AE)
#define BCCI_0327 (0x06AE0CC0)
#define BCCI_0328 (0x06AE0B74)
#define BCCI_0329 (0x06AE0CB8)
#define BCCI_032A (0x06AE0B80)
#define BCCI_032B (0x06AE0290)
#define BCCI_032C (0x06AE0B14)
#define BCCI_032D (0x0AD80CC8)
#define BCCI_032E (0x06AE0C68)
#define BCCI_032F (0x06AE0280)
#define BCCI_0330 (0x00000342)
#define BCCI_0331 (0x03420CC0)
#define BCCI_0332 (0x03420B74)
#define BCCI_0333 (0x03420CB8)
#define BCCI_0334 (0x03420B80)
#define BCCI_0335 (0x03420290)
#define BCCI_0336 (0x03420B14)
#define BCCI_0337 (0x06AE091A)
#define BCCI_0338 (0x03420C68)
#define BCCI_0339 (0x03420280)
#define BCCI_033A (0x03420A68)
#define BCCI_033B (0x034209DA)
#define BCCI_033C (0x03420928)
#define BCCI_033D (0x03420CC8)
#define BCCI_033E (0x03420148)
#define BCCI_033F (0x03420004)
#define BCCI_0340 (0x00000B06)
#define BCCI_0341 (0x0B060CC0)
#define BCCI_0342 (0x0B060B74)
#define BCCI_0343 (0x0B060CB8)
#define BCCI_0344 (0x0B060B80)
#define BCCI_0345 (0x0B060290)
#define BCCI_0346 (0x0B060B14)
#define BCCI_0347 (0x06AE034C)
#define BCCI_0348 (0x0B060C68)
#define BCCI_0349 (0x0B060280)
#define BCCI_034A (0x0B060A68)
#define BCCI_034B (0x0B0609DA)
#define BCCI_034C (0x000009BA)
#define BCCI_034D (0x00000AFA)
#define BCCI_034E (0x0AFA0CC0)
#define BCCI_034F (0x0AFA0B74)
#define BCCI_0350 (0x0AFA0CB8)
#define BCCI_0351 (0x0AFA0B80)
#define BCCI_0352 (0x0AFA0290)
#define BCCI_0353 (0x0AFA0B14)
#define BCCI_0354 (0x09BA0C68)
#define BCCI_0355 (0x0AFA0C68)
#define BCCI_0356 (0x0AFA0280)
#define BCCI_0357 (0x0AFA0A68)
#define BCCI_0358 (0x0AFA09DA)
#define BCCI_0359 (0x0AFA0928)
#define BCCI_035A (0x0AFA0CC8)
#define BCCI_035B (0x00000C5A)
#define BCCI_035C (0x0C5A0CC0)
#define BCCI_035D (0x0C5A0B74)
#define BCCI_035E (0x0C5A0CB8)
#define BCCI_035F (0x0C5A0B80)
#define BCCI_0360 (0x0C5A0290)
#define BCCI_0361 (0x0C5A0B14)
#define BCCI_0362 (0x09BA02F4)
#define BCCI_0363 (0x0C5A0C68)
#define BCCI_0364 (0x0C5A0280)
#define BCCI_0365 (0x0C5A0A68)
#define BCCI_0366 (0x0C5A09DA)
#define BCCI_0367 (0x0C5A0928)
#define BCCI_0368 (0x0C5A0CC8)
#define BCCI_0369 (0x0C5A0148)
#define BCCI_036A (0x0C5A0004)
#define BCCI_036B (0x0C5A0B98)
#define BCCI_036C (0x0C5A091A)
#define BCCI_036D (0x0C5A03EA)
#define BCCI_036E (0x0C5A0480)
#define BCCI_036F (0x0C5A0930)
#define BCCI_0370 (0x09BA0940)
#define BCCI_0371 (0x0C5A02F4)
#define BCCI_0372 (0x06AE0964)
#define BCCI_0373 (0x0C5A099C)
#define BCCI_0374 (0x0C5A0AE0)
#define BCCI_0375 (0x0C5A0BAA)
#define BCCI_0376 (0x0C5A0C56)
#define BCCI_0377 (0x0C5A0C60)
#define BCCI_0378 (0x09BA0948)
#define BCCI_0379 (0x0AFA0948)
#define BCCI_037A (0x0C5A067C)
#define BCCI_037B (0x0C5A0BA4)
#define BCCI_037C (0x0C5A034C)
#define BCCI_037D (0x0AFA094C)
#define BCCI_037E (0x00000C52)
#define BCCI_037F (0x0C520CC0)
#define BCCI_0380 (0x0C520B74)
#define BCCI_0381 (0x0C520CB8)
#define BCCI_0382 (0x0C520B80)
#define BCCI_0383 (0x0C520290)
#define BCCI_0384 (0x0C520B14)
#define BCCI_0385 (0x00000E70)
#define BCCI_0386 (0x0E700CC0)
#define BCCI_0387 (0x0E700B74)
#define BCCI_0388 (0x0E700CB8)
#define BCCI_0389 (0x0E700B80)
#define BCCI_038A (0x0E700290)
#define BCCI_038B (0x0E700B14)
#define BCCI_038C (0x0C520148)
#define BCCI_038D (0x0E700C68)
#define BCCI_038E (0x0E700280)
#define BCCI_038F (0x0E700A68)
#define BCCI_0390 (0x0E7009DA)
#define BCCI_0391 (0x0E700928)
#define BCCI_0392 (0x0E700CC8)
#define BCCI_0393 (0x0E700148)
#define BCCI_0394 (0x0E700004)
#define BCCI_0395 (0x0E700B98)
#define BCCI_0396 (0x0E70091A)
#define BCCI_0397 (0x0E7003EA)
#define BCCI_0398 (0x0E700480)
#define BCCI_0399 (0x0E700930)
#define BCCI_039A (0x0C520C60)
#define BCCI_039B (0x0E7002F4)
#define BCCI_039C (0x0C5A0B20)
#define BCCI_039D (0x0E70099C)
#define BCCI_039E (0x0E700AE0)
#define BCCI_039F (0x0E700BAA)
#define BCCI_03A0 (0x000001AE)
#define BCCI_03A1 (0x01AE0CC0)
#define BCCI_03A2 (0x01AE0B74)
#define BCCI_03A3 (0x01AE0CB8)
#define BCCI_03A4 (0x01AE0B80)
#define BCCI_03A5 (0x01AE0290)
#define BCCI_03A6 (0x01AE0B14)
#define BCCI_03A7 (0x0C5A0964)
#define BCCI_03A8 (0x01AE0C68)
#define BCCI_03A9 (0x01AE0280)
#define BCCI_03AA (0x01AE0A68)
#define BCCI_03AB (0x01AE09DA)
#define BCCI_03AC (0x01AE0928)
#define BCCI_03AD (0x01AE0CC8)
#define BCCI_03AE (0x01AE0148)
#define BCCI_03AF (0x01AE0004)
#define BCCI_03B0 (0x01AE0B98)
#define BCCI_03B1 (0x01AE091A)
#define BCCI_03B2 (0x01AE03EA)
#define BCCI_03B3 (0x01AE0480)
#define BCCI_03B4 (0x01AE0930)
#define BCCI_03B5 (0x0E70094C)
#define BCCI_03B6 (0x01AE02F4)
#define BCCI_03B7 (0x0C5A0974)
#define BCCI_03B8 (0x01AE099C)
#define BCCI_03B9 (0x01AE0AE0)
#define BCCI_03BA (0x01AE0BAA)
#define BCCI_03BB (0x01AE0C56)
#define BCCI_03BC (0x01AE0C60)
#define BCCI_03BD (0x0E700954)
#define BCCI_03BE (0x0C520C8C)
#define BCCI_03BF (0x01AE067C)
#define BCCI_03C0 (0x0000041A)
#define BCCI_03C1 (0x041A0CC0)
#define BCCI_03C2 (0x041A0B74)
#define BCCI_03C3 (0x041A0CB8)
#define BCCI_03C4 (0x041A0B80)
#define BCCI_03C5 (0x041A0290)
#define BCCI_03C6 (0x041A0B14)
#define BCCI_03C7 (0x01AE0AD4)
#define BCCI_03C8 (0x041A0C68)
#define BCCI_03C9 (0x041A0280)
#define BCCI_03CA (0x041A0A68)
#define BCCI_03CB (0x041A09DA)
#define BCCI_03CC (0x041A0928)
#define BCCI_03CD (0x041A0CC8)
#define BCCI_03CE (0x041A0148)
#define BCCI_03CF (0x041A0004)
#define BCCI_03D0 (0x041A0B98)
#define BCCI_03D1 (0x041A091A)
#define BCCI_03D2 (0x041A03EA)
#define BCCI_03D3 (0x041A0480)
#define BCCI_03D4 (0x041A0930)
#define BCCI_03D5 (0x0E7009CC)
#define BCCI_03D6 (0x041A02F4)
#define BCCI_03D7 (0x09BA09E6)
#define BCCI_03D8 (0x041A099C)
#define BCCI_03D9 (0x041A0AE0)
#define BCCI_03DA (0x041A0BAA)
#define BCCI_03DB (0x041A0C56)
#define BCCI_03DC (0x041A0C60)
#define BCCI_03DD (0x0E700970)
#define BCCI_03DE (0x0C520978)
#define BCCI_03DF (0x041A067C)
#define BCCI_03E0 (0x00000C6A)
#define BCCI_03E1 (0x0C6A0CC0)
#define BCCI_03E2 (0x0C6A0B74)
#define BCCI_03E3 (0x0C6A0CB8)
#define BCCI_03E4 (0x0C6A0B80)
#define BCCI_03E5 (0x0C6A0290)
#define BCCI_03E6 (0x0C6A0B14)
#define BCCI_03E7 (0x041A0AD4)
#define BCCI_03E8 (0x0C6A0C68)
#define BCCI_03E9 (0x0C6A0280)
#define BCCI_03EA (0x0C6A0A68)
#define BCCI_03EB (0x0C6A09DA)
#define BCCI_03EC (0x0C6A0928)
#define BCCI_03ED (0x0C6A0CC8)
#define BCCI_03EE (0x0C6A0148)
#define BCCI_03EF (0x0C6A0004)
#define BCCI_03F0 (0x00000404)
#define BCCI_03F1 (0x04040CC0)
#define BCCI_03F2 (0x04040B74)
#define BCCI_03F3 (0x04040CB8)
#define BCCI_03F4 (0x04040B80)
#define BCCI_03F5 (0x04040290)
#define BCCI_03F6 (0x04040B14)
#define BCCI_03F7 (0x0AFA06E4)
#define BCCI_03F8 (0x04040C68)
#define BCCI_03F9 (0x04040280)
#define BCCI_03FA (0x04040A68)
#define BCCI_03FB (0x040409DA)
#define BCCI_03FC (0x04040928)
#define BCCI_03FD (0x04040CC8)
#define BCCI_03FE (0x04040148)
#define BCCI_03FF (0x04040004)
//# in-game encrypted values should not reasonably be higher than this

#endif // __BOOTCODE_CIPHER_H__