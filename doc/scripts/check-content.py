#!/usr/bin/env python3
"""Check chapter coverage and imports without building a PDF."""
from pathlib import Path
import re
import sys

root = Path(__file__).resolve().parents[2]
content = root / "content"
errors = []
listings = 0
main = (content / "kactl.tex").read_text()
main = "\n".join(line.split("%", 1)[0] for line in main.splitlines())
enabled = set(re.findall(r"\\kactlchapter\{([^}]+)\}", main))
for chapter in sorted(content.glob("*/chapter.tex")):
    folder = chapter.parent
    if folder.name not in enabled:
        errors.append(f"Chapter missing from kactl.tex: {folder.name}")
    text = "\n".join(line.split("%", 1)[0] for line in chapter.read_text().splitlines())
    seen = set()
    for match in re.finditer(r"\\(kactlimport|import)(?:\[[^]]*\])?\{([^}]+)\}", text):
        kind, name = match.groups()
        if name in seen:
            errors.append(f"Duplicate import: {folder.name}/{name}")
        seen.add(name)
        listings += kind == "kactlimport"
        if not (folder / name).is_file():
            errors.append(f"Missing import: {folder.name}/{name}")
    # Header descriptions may contain their own illustrations; do not require
    # an additional copy in chapter.tex just to count the asset as referenced.
    graphics_text = text + "\n" + "\n".join(
        (folder / name).read_text() for name in sorted(seen)
        if (folder / name).is_file() and (folder / name).suffix in {".h", ".tex"}
    )
    pattern = r"\\(?:includegraphics|kactlillustration)(?:\[[^]]*\])?\{([^}]+)\}"
    for name in re.findall(pattern, graphics_text):
        seen.add(Path(name).name)
        if not (root / name).is_file() and not (content / "tex" / name).is_file():
            errors.append(f"Missing graphic: {name}")
    for path in folder.iterdir():
        if not path.is_file() or path.name == "chapter.tex" or path.suffix == ".gch":
            continue
        # This standalone document includes chapter.tex itself.
        if folder.name == "test-session" and path.name == "test-session.tex":
            continue
        if path.name not in seen:
            errors.append(f"Not included: {path.relative_to(root)}")
# content/tex contains the build package, preprocessor, and shared graphics;
# it is infrastructure rather than a printable notebook chapter.
for error in errors:
    print(error, file=sys.stderr)
if errors:
    sys.exit(1)
print(f"All {len(enabled)} chapters enabled; {listings} listings and all chapter assets referenced.")
