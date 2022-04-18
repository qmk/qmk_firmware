# Using GitHub Actions

[GitHub Actions](https://docs.github.com/en/actions) can be leveraged to automatically build QMK firmware. This can be be useful for a number reasons:

* Local computing platform that cannot run a [build environment](https://docs.qmk.fm/#/newbs_getting_started).
* Customise and develop QMK collaboratively with others.
* Sharing your QMK firmware builds on GitHub.

?> This guide requires a GitHub account with [a fork of QMK](getting_started_github.md) containing your [personal keymaps](newbs_building_firmware#create-a-new-keymap)

## Setting up the workflow

The workflow should be installed in a development branch of your QMK fork that contains your personal keymaps and customisation. Ideally, they should not be in the `master` branch. See [the making changes](newbs_git_using_your_master_branch.md#making-changes) section for details on working with branches.

Perform a `git checkout` to switch to the branch containing your keymaps. Create a `build.yml` file in the folder `~/qmk_firmware/.github/workflows/` with the following workflow content:

```yml
name: Build firmware for keyboards
on: [push, workflow_dispatch]

jobs:
  build:
    runs-on: ubuntu-latest
    container: qmkfm/qmk_cli
    strategy:
      fail-fast: false
# Start of build matrix
# Edit this section for your keyboards and keymaps
      matrix:
        keyboard:
        - clueboard/66/rev4
        keymap:
        - ${{ github.actor }}
# End of build matrix

    steps:

    - name: Checkout QMK
      uses: actions/checkout@v3
      with:
        submodules: recursive

    - name: Build firmware
      id: build
      run: |
        qmk compile -kb ${{ matrix.keyboard }} -km ${{ matrix.keymap }}
        TARGET=$(echo "${{ matrix.keyboard }}" | sed 's#/#_#g')_${{ matrix.keymap }}
        echo "::set-output name=artifact-name::${TARGET}"

    - name: Archive firmware
      uses: actions/upload-artifact@v3
      continue-on-error: true
      with:
        name: ${{ steps.build.outputs.artifact-name }}
        path: |
          *.hex
          *.bin
          *.uf2
```

### Customising the build matrix

Workflow build `matrix:` is where you can list keyboards and keymaps to be compiled. The example above will build the keyboard `clueboard/66/rev4` with a keymap that matches your GitHub username (`${{ github.actor }}`). Change this section accordingly for your keyboard (and keymap if it differs from your GitHub username).

Multiple keyboards and keymaps can be listed together in the build matrix with a `-` prefix. The following example will build firmwares for `crkbd` and `planck` with your username and `via` keymaps:

```yml
      matrix:
        keyboard:
        - crkbd/rev1
        - planck/rev6
        keymap:
        - ${{ github.actor }}
        - via

```

!> Do note that the `build.yml` file requires ***proper indentation*** for every line. Incorrect spacing will trigger workflow syntax errors.

## Submitting the workflow

After customising the workflow file, ensure that a [user keymap](newbs_building_firmware.md#create-a-new-keymap) has been created for every keyboard listed in the workflow matrix. Commit them along with the workflow file `build.yml` to your branch and `git push` the change to GitHub. A push will automatically trigger the build actions.

?> See [GitHub Actions guide](https://docs.github.com/en/actions/learn-github-actions) to learn more about development workflow.

### Downloading compiled firmware

Visit the GitHub page of your QMK fork (e.g. https://github.com/github_user/qmk_firmware) and choose the "**Actions**" tab. On the left "**Workflows**" sidebar, you will find one labelled "**Build firmware for keyboards**" that was initiated by the `build.yml` file.

1. Select "**Build firmware for keyboards**" to display its jobs in the table.
2. Select the latest workflow job in the table to display its status.
3. Successfully compiled firmware can be downloaded under the "**Artifacts**" section below.
4. If there are build errors, review the job log for details.

?> If you are familiar with using [github.dev](https://docs.github.com/en/codespaces/the-githubdev-web-based-editor) web-based editor, keymap files can be edited and committed directly on GitHub to build them online.


