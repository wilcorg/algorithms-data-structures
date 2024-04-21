import csv

import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

insertion_1 = []
insertion_10 = []
insertion_100 = []
quick_1 = []
quick_10 = []
quick_100 = []
hybrid_1 = []
hybrid_10 = []
hybrid_100 = []
kmerge_1 = []
kmerge_10 = []
kmerge_100 = []
dual_quick_1 = []
dual_quick_10 = []
dual_quick_100 = []
quick_1_long = []
quick_10_long = []
quick_100_long = []
hybrid_1_long = []
hybrid_10_long = []
hybrid_100_long = []
kmerge_1_long = []
kmerge_10_long = []
kmerge_100_long = []
dual_quick_1_long = []
dual_quick_10_long = []
dual_quick_100_long = []
merge_1 = []
merge_10 = []
merge_100 = []
merge_1_long = []
merge_10_long = []
merge_100_long = []


class Read:
    @staticmethod
    def read_csv(data: list, filename):
        with open('../dataset/' + filename, 'r') as file:
            csv_reader = csv.reader(file, delimiter=';')
            for index, row in enumerate(csv_reader):
                if index != 0:
                    data.append([int(row[0]), float(row[1]), float(row[2]), float(row[3]), float(row[4])])


class Plot:
    @staticmethod
    def plot_2(source_1, source_2, col_to_parse, result_filename):
        plt.figure(dpi=1200)
        plt.margins(0)
        plt.grid(True)

        for line in source_1:
            plt.scatter(line[0], line[col_to_parse], s=6, c='r')

        for line in source_2:
            plt.scatter(line[0], line[col_to_parse], s=6, c='g')

        plt.xlim(left=0)
        plt.ylim(bottom=0)
        ax = plt.gca()
        ax.xaxis.set_major_formatter(ticker.StrMethodFormatter('{x:.0f}'))
        ax.yaxis.set_major_formatter(ticker.StrMethodFormatter('{x:.0f}'))
        plt.savefig(result_filename)
        plt.close()

    @staticmethod
    def plot_3(source_1, source_2, source_3, col_to_parse, result_filename):
        plt.figure(dpi=1200)
        plt.margins(0)
        plt.grid(True)

        for line in source_1:
            plt.scatter(line[0], line[col_to_parse], s=6, c='r')

        for line in source_2:
            plt.scatter(line[0], line[col_to_parse], s=6, c='g')

        for line in source_3:
            plt.scatter(line[0], line[col_to_parse], s=6, c='b')

        plt.xlim(left=0)
        plt.ylim(bottom=0)
        ax = plt.gca()
        ax.xaxis.set_major_formatter(ticker.StrMethodFormatter('{x:.0f}'))
        ax.yaxis.set_major_formatter(ticker.StrMethodFormatter('{x:.0f}'))
        plt.savefig(result_filename)
        plt.close()

    @staticmethod
    def plot_4(source_1, source_2, source_3, source_4, col_to_parse, result_filename):
        plt.figure(dpi=1200)
        plt.margins(0)
        plt.grid(True)

        for line in source_1:
            plt.scatter(line[0], line[col_to_parse], s=6, c='r')

        for line in source_2:
            plt.scatter(line[0], line[col_to_parse], s=6, c='g')

        for line in source_3:
            plt.scatter(line[0], line[col_to_parse], s=6, c='b')

        for line in source_4:
            plt.scatter(line[0], line[col_to_parse], s=6, c='y')

        plt.xlim(left=0)
        plt.ylim(bottom=0)
        ax = plt.gca()
        ax.xaxis.set_major_formatter(ticker.StrMethodFormatter('{x:.0f}'))
        ax.yaxis.set_major_formatter(ticker.StrMethodFormatter('{x:.0f}'))
        plt.savefig(result_filename)
        plt.close()


Read.read_csv(insertion_1, 'insertion_k=1')
Read.read_csv(insertion_10, 'insertion_k=10')
Read.read_csv(insertion_100, 'insertion_k=100')
Read.read_csv(quick_1, 'quick_k=1')
Read.read_csv(quick_10, 'quick_k=10')
Read.read_csv(quick_100, 'quick_k=100')
Read.read_csv(hybrid_1, 'quick_hybrid_k=1')
Read.read_csv(hybrid_10, 'quick_hybrid_k=10')
Read.read_csv(hybrid_100, 'quick_hybrid_k=100')
Read.read_csv(quick_1_long, 'quick_k=1_long')
Read.read_csv(quick_10_long, 'quick_k=10_long')
Read.read_csv(quick_100_long, 'quick_k=100_long')
Read.read_csv(hybrid_1_long, 'quick_hybrid_k=1_long')
Read.read_csv(hybrid_10_long, 'quick_hybrid_k=10_long')
Read.read_csv(hybrid_100_long, 'quick_hybrid_k=100_long')
Read.read_csv(kmerge_1, 'kmerge_k=1')
Read.read_csv(kmerge_10, 'kmerge_k=10')
Read.read_csv(kmerge_100, 'kmerge_k=100')
Read.read_csv(kmerge_1_long, 'kmerge_k=1_long')
Read.read_csv(kmerge_10_long, 'kmerge_k=10_long')
Read.read_csv(kmerge_100_long, 'kmerge_k=100_long')
Read.read_csv(dual_quick_1, 'dual_pivot_k=1')
Read.read_csv(dual_quick_10, 'dual_pivot_k=10')
Read.read_csv(dual_quick_100, 'dual_pivot_k=100')
Read.read_csv(dual_quick_1_long, 'dual_pivot_k=1_long')
Read.read_csv(dual_quick_10_long, 'dual_pivot_k=10_long')
Read.read_csv(dual_quick_100_long, 'dual_pivot_k=100_long')
Read.read_csv(merge_1, 'merge_k=1')
Read.read_csv(merge_10, 'merge_k=10')
Read.read_csv(merge_100, 'merge_k=100')
Read.read_csv(merge_1_long, 'merge_k=1_long')
Read.read_csv(merge_10_long, 'merge_k=10_long')
Read.read_csv(merge_100_long, 'merge_k=100_long')

Plot.plot_4(insertion_1, quick_1, hybrid_1, dual_quick_1, 1, 'plots/c_1.png')
Plot.plot_4(insertion_10, quick_10, hybrid_10, dual_quick_10, 1, 'plots/c_1.png')
Plot.plot_4(insertion_100, quick_100, hybrid_100, dual_quick_100, 1, 'plots/c_1.png')
Plot.plot_4(insertion_1, quick_1, hybrid_1, dual_quick_1, 2, 'plots/s_1.png')
Plot.plot_4(insertion_10, quick_10, hybrid_10,dual_quick_10, 2, 'plots/s_10.png')
Plot.plot_4(insertion_100, quick_100, hybrid_100,dual_quick_100, 2, 'plots/s_100.png')
Plot.plot_4(insertion_1, quick_1, hybrid_1,dual_quick_1, 3, 'plots/c_n_1.png')
Plot.plot_4(insertion_10, quick_10, hybrid_10,dual_quick_10, 3, 'plots/c_n_10.png')
Plot.plot_4(insertion_100, quick_100, hybrid_100,dual_quick_100, 3, 'plots/c_n_100.png')
Plot.plot_4(insertion_1, quick_1, hybrid_1,dual_quick_1, 4, 'plots/s_n_1.png')
Plot.plot_4(insertion_10, quick_10, hybrid_10,dual_quick_10, 4, 'plots/s_n_10.png')
Plot.plot_4(insertion_100, quick_100, hybrid_100, dual_quick_100, 4, 'plots/s_n_100.png')

Plot.plot_3(quick_1_long, hybrid_1_long, dual_quick_1_long,1, 'plots/c_1_long.png')
Plot.plot_3(quick_10_long, hybrid_10_long, dual_quick_10_long,1, 'plots/c_10_long.png')
Plot.plot_3(quick_100_long, hybrid_100_long,dual_quick_100_long, 1, 'plots/c_100_long.png')
Plot.plot_3(quick_1_long, hybrid_1_long, dual_quick_1_long,2, 'plots/s_1_long.png')
Plot.plot_3(quick_10_long, hybrid_10_long, dual_quick_10_long,2, 'plots/s_10_long.png')
Plot.plot_3(quick_100_long, hybrid_100_long, dual_quick_100_long,2, 'plots/s_100_long.png')
Plot.plot_3(quick_1_long, hybrid_1_long,dual_quick_1_long, 3, 'plots/c_n_1_long.png')
Plot.plot_3(quick_10_long, hybrid_10_long,dual_quick_10_long, 3, 'plots/c_n_10_long.png')
Plot.plot_3(quick_100_long, hybrid_100_long, dual_quick_100_long,3, 'plots/c_n_100_long.png')
Plot.plot_3(quick_1_long, hybrid_1_long,dual_quick_1_long, 4, 'plots/s_n_1_long.png')
Plot.plot_3(quick_10_long, hybrid_10_long, dual_quick_10_long,4, 'plots/s_n_10_long.png')
Plot.plot_3(quick_100_long, hybrid_100_long,dual_quick_100_long, 4, 'plots/s_n_100_long.png')

Plot.plot_2(merge_1, kmerge_1, 1, 'plots/merges_c_1.png')
Plot.plot_2(merge_10, kmerge_10, 1, 'plots/merges_c_10.png')
Plot.plot_2(merge_100, kmerge_100, 1, 'plots/merges_c_100.png')
Plot.plot_2(merge_1_long, kmerge_1_long, 1, 'plots/merges_c_1_long.png')
Plot.plot_2(merge_10_long, kmerge_10_long, 1, 'plots/merges_c_10_long.png')
Plot.plot_2(merge_100_long, kmerge_100_long, 1, 'plots/merges_c_100_long.png')
Plot.plot_2(merge_1, kmerge_1, 2, 'plots/merges_s_1.png')
Plot.plot_2(merge_10, kmerge_10, 2, 'plots/merges_s_10.png')
Plot.plot_2(merge_100, kmerge_100, 2, 'plots/merges_s_100.png')
Plot.plot_2(merge_1_long, kmerge_1_long, 2, 'plots/merges_s_1_long.png')
Plot.plot_2(merge_10_long, kmerge_10_long, 2, 'plots/merges_s_10_long.png')
Plot.plot_2(merge_100_long, kmerge_100_long, 2, 'plots/merges_s_100_long.png')
Plot.plot_2(merge_1, kmerge_1, 3, 'plots/merges_c_n_1.png')
Plot.plot_2(merge_10, kmerge_10, 3, 'plots/merges_c_n_10.png')
Plot.plot_2(merge_100, kmerge_100, 3, 'plots/merges_c_n_100.png')
Plot.plot_2(merge_1_long, kmerge_1_long, 3, 'plots/merges_c_n_1_long.png')
Plot.plot_2(merge_10_long, kmerge_10_long, 3, 'plots/merges_c_n_10_long.png')
Plot.plot_2(merge_100_long, kmerge_100_long, 3, 'plots/merges_c_n_100_long.png')
Plot.plot_2(merge_1, kmerge_1, 4, 'plots/merges_s_n_1.png')
Plot.plot_2(merge_10, kmerge_10, 4, 'plots/merges_s_n_10.png')
Plot.plot_2(merge_100, kmerge_100, 4, 'plots/merges_s_n_100.png')
Plot.plot_2(merge_1_long, kmerge_1_long, 4, 'plots/merges_s_n_1_long.png')
Plot.plot_2(merge_10_long, kmerge_10_long, 4, 'plots/merges_s_n_10_long.png')
Plot.plot_2(merge_100_long, kmerge_100_long, 4, 'plots/merges_s_n_100_long.png')
