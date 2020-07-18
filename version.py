import argparse


# v<RELEASE_VERSION>.<MAJOR_PATCH><MINOR_PATCH><RELEASE_CANIDATE>

# Windows CMD: for /f %i in ('python version.py -v %VERSION%') do set VERSION=%i

_VERSION_MINOR_LIMIT = 20
_VERSION_RC_LIMIT = 5


if __name__ == '__main__':
    argparser = argparse.ArgumentParser(description='Versionierungs Tool')

    argparser.add_argument('-v', dest='version', required=True)
    argparser.add_argument('--verify-control-service',
                           dest='verify', action='store_true', default=False)
    argparser.add_argument(
        '--rc', dest='rc', action='store_true', default=False)
    args = argparser.parse_args()

    #print(f'version: {args.version}')
    new_version = ''
    if(args.version[0] == 'v'):
        args.version = args.version.replace('v', 'v.')
    else:
        raise Exception("wrong version format")

    full_version = args.version.split('.')
    if(len(full_version) == 4 and full_version[0] == 'v'):
        _, release_version, major_patch_version, minor_patch_version = full_version
        new_version = f'v{release_version}.'
        if('-rc' in minor_patch_version):
            minor_patch_version, rc_version = minor_patch_version.split('-rc')
            if(not rc_version):
                raise Exception("no release canidate version")
            if(args.rc and int(rc_version) < _VERSION_RC_LIMIT):
                rc_version = str(int(rc_version) + 1)
                new_version = new_version + \
                    f'{major_patch_version}.{minor_patch_version}-rc{rc_version}'
            elif(args.rc and int(minor_patch_version) < _VERSION_MINOR_LIMIT):
                minor_patch_version = str(int(minor_patch_version) + 1)
                new_version = new_version + \
                    f'{major_patch_version}.{minor_patch_version}-rc0'
            elif(args.rc):
                minor_patch_version = '0'
                major_patch_version = str(int(major_patch_version) + 1)
                new_version = new_version + \
                    f'{major_patch_version}.{minor_patch_version}-rc0'

            elif(int(minor_patch_version) < _VERSION_MINOR_LIMIT):
                minor_patch_version = str(int(minor_patch_version) + 1)
                new_version = new_version + \
                    f'{major_patch_version}.{minor_patch_version}'
            else:
                minor_patch_version = '0'
                major_patch_version = str(int(major_patch_version) + 1)
                new_version = new_version + \
                    f'{major_patch_version}.{minor_patch_version}'
        elif(args.rc):
            new_version = new_version + \
                f'{major_patch_version}.{minor_patch_version}-rc0'
        else:
            if(int(minor_patch_version) < _VERSION_MINOR_LIMIT):
                minor_patch_version = str(int(minor_patch_version) + 1)
                new_version = new_version + \
                    f'{major_patch_version}.{minor_patch_version}'
            else:
                minor_patch_version = '0'
                major_patch_version = str(int(major_patch_version) + 1)
                new_version = new_version + \
                    f'{major_patch_version}.{minor_patch_version}'

    else:
        raise Exception("wrong version format")

    print(new_version)
