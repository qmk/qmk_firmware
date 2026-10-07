from __future__ import annotations

import os
import subprocess
import unittest
from pathlib import Path
from tempfile import TemporaryDirectory
from typing import List, Union, override

import qmk.git

# pyright: reportUnusedCallResult=false


def run_git(dir: Union[Path, None], args: List[Union[str, Path]]):
    dir_args = [] if dir is None else ["-C", dir]

    try:
        subprocess.run(
            ["git", *dir_args, *args],
            capture_output=True,
            check=True,

            # Prevent the user's config from leaking in.
            env={
                **os.environ, "GIT_CONFIG_GLOBAL": "/dev/null"
            },
            text=True,
        )
    except subprocess.CalledProcessError as error:
        print(error.stderr)

        raise


class GitTest(unittest.TestCase):
    temp_dir: Union[TemporaryDirectory[str], None] = None

    @override
    def setUp(self) -> None:
        try:
            self.temp_dir = TemporaryDirectory()
            temp_path = Path(self.temp_dir.name)
            self.sub_origin = temp_path / "sub_origin"

            # These are the three paths which tests should operate on.
            self.main = temp_path / "main"
            self.work = temp_path / "work"
            self.sub = self.main / "sub"

            # Create the repo for the submodule and add a commit to it.
            run_git(None, ["init", "-b", "branch-sub", self.sub_origin])
            run_git(self.sub_origin, ["config", "user.email", "sub_origin"])
            run_git(self.sub_origin, ["config", "user.name", "sub_origin"])
            (self.sub_origin / "sub.txt").write_text("sub")
            run_git(self.sub_origin, ["add", "sub.txt"])
            run_git(self.sub_origin, ["commit", "-m", "sub"])

            # Create the main repo and add the submodule to it.
            run_git(None, ["init", "-b", "branch-main", self.main])
            run_git(self.main, ["config", "user.email", "main"])
            run_git(self.main, ["config", "user.name", "main"])
            run_git(
                self.main,
                [
                    "-c",
                    # By default, Git will refuse to add a submodule using the
                    # file: protocol for reasons which don't apply to these
                    # tests.
                    #
                    # See: <https://github.com/git/git/blob/master/Documentation/RelNotes/2.30.6.adoc>
                    "protocol.file.allow=always",
                    "submodule",
                    "add",
                    self.sub_origin,
                    "sub",
                ],
            )
            run_git(self.main, ["commit", "-m", "main"])
            run_git(self.sub, ["config", "user.email", "sub"])
            run_git(self.sub, ["config", "user.name", "sub"])

            # Create a worktree for a new branch "work" and add a commit to it.
            run_git(self.main, ["worktree", "add", "-b", "branch-work", self.work])
            (self.work / "work.txt").write_text("work")
            run_git(self.work, ["add", "work.txt"])
            run_git(self.work, ["commit", "-m", "work"])
        except subprocess.CalledProcessError:
            self.tearDown()

            raise

    @override
    def tearDown(self) -> None:
        if self.temp_dir is not None:
            self.temp_dir.cleanup()

    def test_git_check_deviation(self) -> None:
        # git_check_deviation fetches from a remote named "upstream".
        run_git(self.sub, ["remote", "add", "upstream", self.sub_origin])

        os.chdir(self.sub)
        self.assertFalse(qmk.git.git_check_deviation("branch-sub"))

        # Add a commit on top of the local branch, causing it to deviate from
        # the remote tracking branch.
        (self.sub / "another-file.txt").write_text("something custom")
        run_git(self.sub, ["add", "another-file.txt"])
        run_git(self.sub, ["commit", "-m", "added something custom"])

        os.chdir(self.sub)
        self.assertTrue(qmk.git.git_check_deviation("branch-sub"))

    def test_git_check_repo(self) -> None:
        self.assertTrue(qmk.git.git_check_repo(self.main))
        self.assertTrue(qmk.git.git_check_repo(self.work))
        self.assertTrue(qmk.git.git_check_repo(self.sub))

        with TemporaryDirectory() as not_a_repo:
            not_a_repo = Path(not_a_repo)

            self.assertFalse(qmk.git.git_check_repo(not_a_repo))

            (not_a_repo / ".git").write_text("absolute gibberish")
            self.assertFalse(qmk.git.git_check_repo(not_a_repo))

            (not_a_repo / ".git").write_text("gitdir: <!not a real path!>")
            self.assertFalse(qmk.git.git_check_repo(not_a_repo))

    @unittest.skip("would require changing file/directory ownership")
    def test_git_check_safe(self) -> None:
        raise NotImplementedError

    def test_git_common_ancestor(self) -> None:
        # In the main repo, add a new branch with a commit, to diverge from the
        # worktree branch.
        run_git(self.main, ["checkout", "-b", "branch-diverged"])
        (self.main / "diverged.txt").write_text("diverged")
        run_git(self.main, ["add", "diverged.txt"])
        run_git(self.main, ["commit", "-m", "diverged"])

        os.chdir(self.main)
        self.assertIsNotNone(qmk.git.git_get_common_ancestor("branch-work", "branch-diverged"))

    def test_git_get_branch(self) -> None:
        os.chdir(self.main)
        self.assertEqual("branch-main", qmk.git.git_get_branch())

        os.chdir(self.work)
        self.assertEqual("branch-work", qmk.git.git_get_branch())

        os.chdir(self.sub)
        self.assertEqual("branch-sub", qmk.git.git_get_branch())

    def test_git_get_ignored_files(self) -> None:
        # Add some ignored files to each repo.
        (self.main / ".gitignore").write_text(".gitignore\ndiverged.ignored\n")
        (self.main / "diverged.ignored").write_text("diverged, but ignored")
        (self.work / ".gitignore").write_text(".gitignore\nwork.ignored\n")
        (self.work / "work.ignored").write_text("work, but ignored")
        (self.sub / ".gitignore").write_text(".gitignore\nsub.ignored\n")
        (self.sub / "sub.ignored").write_text("sub, but ignored")

        os.chdir(self.main)
        self.assertEqual([".gitignore", "diverged.ignored"], qmk.git.git_get_ignored_files())

        os.chdir(self.work)
        self.assertEqual([".gitignore", "work.ignored"], qmk.git.git_get_ignored_files())

        os.chdir(self.sub)
        self.assertEqual([".gitignore", "sub.ignored"], qmk.git.git_get_ignored_files())

    def test_git_get_last_log_entry(self) -> None:
        os.chdir(self.main)
        self.assertIsNotNone(qmk.git.git_get_last_log_entry("branch-main"))

        os.chdir(self.work)
        self.assertIsNotNone(qmk.git.git_get_last_log_entry("branch-work"))

        os.chdir(self.sub)
        self.assertIsNotNone(qmk.git.git_get_last_log_entry("branch-sub"))

    def test_git_get_qmk_hash(self) -> None:
        os.chdir(self.main)
        self.assertIsNotNone(qmk.git.git_get_qmk_hash())

        os.chdir(self.work)
        self.assertIsNotNone(qmk.git.git_get_qmk_hash())

        os.chdir(self.sub)
        self.assertIsNotNone(qmk.git.git_get_qmk_hash())

    def test_git_get_remotes(self) -> None:
        # Only the main repo needs a remote added; the worktree uses the same
        # remotes as its repo and the submodule already has a remote.
        run_git(self.main, ["remote", "add", "main", "http://:0/"])

        os.chdir(self.main)
        self.assertDictEqual({"main": {"url": "http://:0/"}}, qmk.git.git_get_remotes())

        os.chdir(self.work)
        self.assertDictEqual({"main": {"url": "http://:0/"}}, qmk.git.git_get_remotes())

        os.chdir(self.sub)
        self.assertDictEqual({"origin": {"url": str(self.sub_origin)}}, qmk.git.git_get_remotes())

    def test_git_get_tag(self) -> None:
        os.chdir(self.main)
        self.assertIsNone(qmk.git.git_get_tag())

        os.chdir(self.work)
        self.assertIsNone(qmk.git.git_get_tag())

        os.chdir(self.sub)
        self.assertIsNone(qmk.git.git_get_tag())

        run_git(self.main, ["tag", "-am", "main", "tag-main"])
        run_git(self.work, ["tag", "-am", "work", "tag-work"])
        run_git(self.sub, ["tag", "-am", "sub", "tag-sub"])

        os.chdir(self.main)
        self.assertEqual("tag-main", qmk.git.git_get_tag())

        os.chdir(self.work)
        self.assertEqual("tag-work", qmk.git.git_get_tag())

        os.chdir(self.sub)
        self.assertEqual("tag-sub", qmk.git.git_get_tag())

    def test_git_get_username(self) -> None:
        os.chdir(self.main)
        self.assertEqual("main", qmk.git.git_get_username())

        # Worktrees use the same config as their associated repo.
        os.chdir(self.work)
        self.assertEqual("main", qmk.git.git_get_username())

        os.chdir(self.sub)
        self.assertEqual("sub", qmk.git.git_get_username())

    def test_git_get_version(self) -> None:
        run_git(self.main, ["tag", "-am", "tagged v1", "v1"])
        run_git(self.work, ["tag", "-am", "tagged v2", "v2"])
        run_git(self.sub, ["tag", "-am", "tagged v3", "v3"])

        self.assertEqual("v1", qmk.git.git_get_version(self.main))
        self.assertEqual("v2", qmk.git.git_get_version(self.work))
        self.assertEqual("v3", qmk.git.git_get_version(self.sub))

        (self.main / "main.txt").write_text("main-dirty")
        (self.work / "work.txt").write_text("work-dirty")
        (self.sub / "sub.txt").write_text("sub-dirty")

        self.assertEqual("v1-dirty", qmk.git.git_get_version(self.main))
        self.assertEqual("v2-dirty", qmk.git.git_get_version(self.work))
        self.assertEqual("v3-dirty", qmk.git.git_get_version(self.sub))

    def test_git_is_dirty(self) -> None:
        # No changes.

        os.chdir(self.main)
        self.assertFalse(qmk.git.git_is_dirty())

        os.chdir(self.work)
        self.assertFalse(qmk.git.git_is_dirty())

        os.chdir(self.sub)
        self.assertFalse(qmk.git.git_is_dirty())

        # Unstaged changes only.

        (self.main / "main.txt").write_text("main-dirty")
        (self.work / "work.txt").write_text("work-dirty")
        (self.sub / "sub.txt").write_text("sub-dirty")

        os.chdir(self.main)
        self.assertTrue(qmk.git.git_is_dirty())

        os.chdir(self.work)
        self.assertTrue(qmk.git.git_is_dirty())

        os.chdir(self.sub)
        self.assertTrue(qmk.git.git_is_dirty())

        # staged changes only.

        run_git(self.main, ["add", "main.txt"])
        run_git(self.work, ["add", "work.txt"])
        run_git(self.sub, ["add", "sub.txt"])

        os.chdir(self.main)
        self.assertTrue(qmk.git.git_is_dirty())

        os.chdir(self.work)
        self.assertTrue(qmk.git.git_is_dirty())

        os.chdir(self.sub)
        self.assertTrue(qmk.git.git_is_dirty())

        # Both staged and unstaged changes.

        (self.main / "main.txt").write_text("main-dirtier")
        (self.work / "work.txt").write_text("work-dirtier")
        (self.sub / "sub.txt").write_text("sub-dirtier")

        os.chdir(self.main)
        self.assertTrue(qmk.git.git_is_dirty())

        os.chdir(self.work)
        self.assertTrue(qmk.git.git_is_dirty())

        os.chdir(self.sub)
        self.assertTrue(qmk.git.git_is_dirty())
