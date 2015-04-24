"""Just a template for subclassing"""
import uuid, shutil, os, logging, fnmatch
from os import walk, remove
from os.path import join, dirname, isdir, split
from copy import copy
from jinja2 import Template, FileSystemLoader
from jinja2.environment import Environment
from contextlib import closing
from zipfile import ZipFile, ZIP_DEFLATED

from workspace_tools.utils import mkdir
from workspace_tools.toolchains import TOOLCHAIN_CLASSES
from workspace_tools.targets import TARGET_MAP

class OldLibrariesException(Exception): pass

class Exporter():
    TEMPLATE_DIR = dirname(__file__)
    DOT_IN_RELATIVE_PATH = False

    def __init__(self, target, inputDir, program_name, build_url_resolver, extra_symbols=None):
        self.inputDir = inputDir
        self.target = target
        self.program_name = program_name
        self.toolchain = TOOLCHAIN_CLASSES[self.get_toolchain()](TARGET_MAP[target])
        self.build_url_resolver = build_url_resolver
        jinja_loader = FileSystemLoader(os.path.dirname(os.path.abspath(__file__)))
        self.jinja_environment = Environment(loader=jinja_loader)
        self.extra_symbols = extra_symbols

    def get_toolchain(self):
        return self.TOOLCHAIN

    def __scan_and_copy(self, src_path, trg_path):
        resources = self.toolchain.scan_resources(src_path)

        for r_type in ['headers', 's_sources', 'c_sources', 'cpp_sources',
            'objects', 'libraries', 'linker_script',
            'lib_builds', 'lib_refs', 'repo_files', 'hex_files', 'bin_files']:
            r = getattr(resources, r_type)
            if r:
                self.toolchain.copy_files(r, trg_path, rel_path=src_path)
        return resources

    def __scan_all(self, path):
        resources = []

        for root, dirs, files in walk(path):
            for d in copy(dirs):
                if d == '.' or d == '..':
                    dirs.remove(d)

            for file in files:
                file_path = join(root, file)
                resources.append(file_path)

        return resources

    def scan_and_copy_resources(self, prj_path, trg_path):
        # Copy only the file for the required target and toolchain
        lib_builds = []
        for src in ['lib', 'src']:
            resources = self.__scan_and_copy(join(prj_path, src), trg_path)
            lib_builds.extend(resources.lib_builds)

            # The repository files
            for repo_dir in resources.repo_dirs:
                repo_files = self.__scan_all(repo_dir)
                self.toolchain.copy_files(repo_files, trg_path, rel_path=join(prj_path, src))

        # The libraries builds
        for bld in lib_builds:
            build_url = open(bld).read().strip()
            lib_data = self.build_url_resolver(build_url)
            lib_path = lib_data['path'].rstrip('\\/')
            self.__scan_and_copy(lib_path, join(trg_path, lib_data['name']))

            # Create .hg dir in mbed build dir so it's ignored when versioning
            hgdir = join(trg_path, lib_data['name'], '.hg')
            mkdir(hgdir)
            fhandle = file(join(hgdir, 'keep.me'), 'a')
            fhandle.close()

        # Final scan of the actual exported resources
        self.resources = self.toolchain.scan_resources(trg_path)
        self.resources.relative_to(trg_path, self.DOT_IN_RELATIVE_PATH)
        # Check the existence of a binary build of the mbed library for the desired target
        # This prevents exporting the mbed libraries from source
        # if not self.toolchain.mbed_libs:
        #    raise OldLibrariesException()

    def gen_file(self, template_file, data, target_file):
        template_path = join(Exporter.TEMPLATE_DIR, template_file)
        template = self.jinja_environment.get_template(template_file)
        target_text = template.render(data)

        target_path = join(self.inputDir, target_file)
        logging.debug("Generating: %s" % target_path)
        open(target_path, "w").write(target_text)

    def get_symbols(self, add_extra_symbols=True):
        """ This function returns symbols which must be exported.
            Please add / overwrite symbols in each exporter separately
        """
        symbols = self.toolchain.get_symbols()
        # We have extra symbols from e.g. libraries, we want to have them also added to export
        if add_extra_symbols:
            if self.extra_symbols is not None:
                symbols.extend(self.extra_symbols)
        return symbols

def zip_working_directory_and_clean_up(tempdirectory=None, destination=None, program_name=None, clean=True):
    uid = str(uuid.uuid4())
    zipfilename = '%s.zip'%uid

    logging.debug("Zipping up %s to %s" % (tempdirectory,  join(destination, zipfilename)))
    # make zip
    def zipdir(basedir, archivename):
        assert isdir(basedir)
        fakeroot = program_name + '/'
        with closing(ZipFile(archivename, "w", ZIP_DEFLATED)) as z:
            for root, _, files in os.walk(basedir):
                # NOTE: ignore empty directories
                for fn in files:
                    absfn = join(root, fn)
                    zfn = fakeroot + '/' +  absfn[len(basedir)+len(os.sep):]
                    z.write(absfn, zfn)

    zipdir(tempdirectory, join(destination, zipfilename))

    if clean:
        shutil.rmtree(tempdirectory)

    return join(destination, zipfilename)
