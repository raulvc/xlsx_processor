# -*- coding: utf-8 -*-

from gooey import Gooey, GooeyParser
import pandas
import os
import subprocess

SCRIPT_PATH = os.path.dirname(os.path.realpath(__file__))


class Wrapper:
    def __init__(self):
        self.csv_files = []

    def start(self, params):
        self.prepare_data(params.files)
        criteria = [params.line_criteria, params.fvalley_criteria, params.fpeak_criteria, params.defvalley_criteria,
                    params.defpeak_criteria]
        self.process(params.processor, criteria)

    def process(self, processor_path, criteria):
        # building command string
        criteria_str = " ".join(str(cr) for cr in criteria)
        files_str = " ".join(self.csv_files)
        cmd = " ".join([processor_path, criteria_str, files_str])
        print u'Processing files...'
        print cmd


    def prepare_data(self, files):
        # converting xlsx files to csv
        file_index = 1
        for filename in files:
            print u'Converting "%s" to csv...' % os.path.basename(filename)
            xlsx_file = pandas.ExcelFile(filename)
            for sheet in xlsx_file.sheet_names:
                csv_file = xlsx_file.parse(sheet, index_col=None)
                csv_filename = 'temp_%02d.csv' % file_index
                print u'Converting sheet "%s" to "%s"' % (sheet, csv_filename)
                csv_file.to_csv(csv_filename)
                # keeping a list of absolute csv file paths
                self.csv_files.append(os.path.join(SCRIPT_PATH, csv_filename))
                file_index += 1


@Gooey(program_name="XLSX Processing", optional_cols=2)
def parse_args():
    parser = GooeyParser()
    parser.add_argument('files', type=unicode, nargs='+', widget='MultiFileChooser',
                        help=u'xlsx files to be processed')
    parser.add_argument('output', type=unicode, widget='FileSaver',
                        help=u'csv file to be saved', default=os.path.join(SCRIPT_PATH, 'results.csv'))
    parser.add_argument('processor', type=unicode, widget='FileChooser',
                        help=u'processor executable', default=os.path.join(SCRIPT_PATH, "processor"))
    parser.add_argument('-t', '--tolerance', type=int, dest='line_criteria',
                        help=u'min lines criteria until next peak/valley', default=5)
    parser.add_argument('--fvalley', type=float, dest='fvalley_criteria',
                        help=u'[force] min value criteria until next valley', default=5000)
    parser.add_argument('--fpeak', type=float, dest='fpeak_criteria',
                        help=u'[force] min value criteria until next peak', default=16000)
    parser.add_argument('--defvalley', type=float, dest='defvalley_criteria',
                        help=u'[deformation] min value criteria until next valley', default=400)
    parser.add_argument('--defpeak', type=float, dest='defpeak_criteria',
                        help=u'[deformation] min value criteria until next peak', default=1200)
    return parser.parse_args()


if __name__ == '__main__':
    args = parse_args()
    wrapper = Wrapper()
    wrapper.start(args)
