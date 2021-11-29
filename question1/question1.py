import re
import pandas as pd

file = 'Question1.sam'
with open(file, 'r') as f:
    lines = f.readlines()
    chr_counts = pd.Series([0 for i in range(23)], index=["chr%d" % j for j in range(1, 23)] + ['Total'])
    ACGT_counts = pd.Series([0 for i in range(5)], index=['A', 'C', 'G', 'T', 'Total'])
    MDI_counts = pd.Series([0 for i in range(4)], index=['M', 'D', 'I', 'Total'])
    MDZ_ACGT_counts = pd.Series([0 for i in range(5)], index=['A', 'C', 'G', 'T', 'Total'])
    for line in lines:
        line = line.strip()
        sam = line.split('\t')
        if 'XT:A:U' in sam:
            # 统计分别属于chr1-22的行数
            if sam[2] in list(chr_counts.index)[0: -1]:
                chr_counts[sam[2]] += 1

            # 统计所有行中第十列中A、C、G、T字符分别出现的次数
            ACGT_counts['A'] += sam[9].count('A')
            ACGT_counts['C'] += sam[9].count('C')
            ACGT_counts['G'] += sam[9].count('G')
            ACGT_counts['T'] += sam[9].count('T')


            # 统计所有行中第六列M、D、I分别的频次
            pattern_M = re.compile('([0-9]*)M')
            MDI_counts['M'] += sum([int(n) for n in pattern_M.findall(sam[5])] if pattern_M.findall(sam[5]) else [])
            pattern_D = re.compile('([0-9]*)D')
            MDI_counts['D'] += sum([int(n) for n in pattern_D.findall(sam[5])] if pattern_D.findall(sam[5]) else [])
            pattern_I = re.compile('([0-9]*)I')
            MDI_counts['I'] += sum([int(n) for n in pattern_I.findall(sam[5])] if pattern_I.findall(sam[5]) else [])

            # 统计所有行中第十七列(MD:Z:开头)中“^”后面字母分别的次数
            pattern = re.compile('^MD:Z:')
            if pattern.match(sam[16]):
                pattern_A = re.compile('\^A(\d+)')
                MDZ_ACGT_counts['A'] += sum([int(n) for n in pattern_A.findall(sam[16])])
                pattern_C = re.compile('\^C(\d+)')
                MDZ_ACGT_counts['C'] += sum([int(n) for n in pattern_C.findall(sam[16])])
                pattern_G = re.compile('\^G(\d+)')
                MDZ_ACGT_counts['G'] += sum([int(n) for n in pattern_G.findall(sam[16])])
                pattern_T = re.compile('\^T(\d+)')
                MDZ_ACGT_counts['T'] += sum([int(n) for n in pattern_T.findall(sam[16])])

    chr_counts['Total'] = sum(chr_counts[0:-1])
    ACGT_counts['Total'] = sum(ACGT_counts[0:-1])
    MDI_counts['Total'] = sum(MDI_counts[0:-1])
    MDZ_ACGT_counts['Total'] = sum(MDZ_ACGT_counts[0:-1])

chr_counts.to_csv('chr1-22的行数.csv',  header=False)
ACGT_counts.to_csv('A、C、G、T分别出现的次数.csv', header=False)
MDI_counts.to_csv('M、D、I分别的频次.csv', header=False)
MDZ_ACGT_counts.to_csv('^后面ACGT分别的次数.csv', header=False)
