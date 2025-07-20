# QMK Firmware Fork Git Workflow Cheat Sheet

## 📋 Purpose

Maintain your fork of QMK firmware:

- Keep your fork up-to-date with the upstream `qmk/qmk_firmware`.
- Safely develop your own configurations without risk of upstream overwriting your work.

---

## 🧭 Remotes Setup

### Clone your fork

```bash
git clone git@github.com:<your-username>/qmk_firmware.git
cd qmk_firmware
```

### Add upstream remote

```bash
git remote add upstream https://github.com/qmk/qmk_firmware.git
git fetch upstream
```

### Verify remotes

```bash
git remote -v
```

Should show:

```
origin    git@github.com:<your-username>/qmk_firmware.git (fetch)
origin    git@github.com:<your-username>/qmk_firmware.git (push)
upstream  https://github.com/qmk/qmk_firmware.git (fetch)
upstream  https://github.com/qmk/qmk_firmware.git (push)
```

---

## 🔄 Sync with Upstream

### Update your master branch

```bash
git checkout master
git fetch upstream
git merge upstream/master
git push origin master
```

---

## 🛠️ Create a Feature Branch

### Start a new branch for your work

```bash
git checkout master
git checkout -b <your-feature-branch>
```

Recommended naming convention:

```bash
<username>/<feature-name>
```

Example:

```bash
git checkout -b mikehiga/my_keyboard_config
```

---

## 👨‍💻 Work on Your Branch

### Make and commit changes

```bash
# edit files under keyboards/ or users/
git add .
git commit -m "Add my keyboard configuration"
git push origin <your-feature-branch>
```

You can continue working on this branch and push updates as needed.

---

## 🔄 Sync Feature Branch with Upstream Changes

When QMK upstream is updated and you want to incorporate changes:

### Sync your master

```bash
git checkout master
git fetch upstream
git merge upstream/master
git push origin master
```

### Merge master into your feature branch

```bash
git checkout <your-feature-branch>
git merge master
```

If there are merge conflicts, resolve them, then:

```bash
git add .
git commit
git push origin <your-feature-branch>
```

---

## 🧹 Best Practices

- Never work directly on `master`.
- Keep your work isolated to your own feature branches.
- Place your configurations in `keyboards/<your-board>` or `users/<yourname>` to minimize conflicts.
- Sync upstream regularly.

---

## 🔗 References

- [QMK Git Guide](https://docs.qmk.fm/newbs_git_using_your_master_branch)
