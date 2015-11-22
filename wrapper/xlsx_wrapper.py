# -*- coding: utf-8 -*-

from gooey import Gooey, GooeyParser
import os
from subprocess import Popen, PIPE
import sys

SCRIPT_PATH = os.path.dirname(os.path.realpath(__file__))
PYTHON_PATH = sys.executable
CONVERTER_PATH = os.path.join(SCRIPT_PATH, "xlsx2csv.py")


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
        self.open_subprocess(cmd)

    def prepare_data(self, files):
        # converting xlsx files to csv
        file_index = 1
        for filename in files:
            csv_filename = 'temp_%02d.csv' % file_index
            cmd = " ".join([PYTHON_PATH, CONVERTER_PATH, filename, csv_filename])
            print u'Converting "%s" to "%s"...' % (os.path.basename(filename), csv_filename)
            self.open_subprocess(cmd)
            self.csv_files.append(os.path.join(SCRIPT_PATH, csv_filename))
            file_index += 1

    @staticmethod
    def open_subprocess(cmd):
        subprocess = Popen(cmd, stdout=PIPE, shell=True)
        stdout, stderr = subprocess.communicate()
        result = stdout.split('\n')
        for line in result:
            print line
        if stderr:
            print stderr
            sys.exit(1)


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
