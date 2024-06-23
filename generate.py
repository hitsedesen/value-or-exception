from jinja2 import Environment, FileSystemLoader, select_autoescape
from pathlib import Path
import sys

assert len(sys.argv) == 3, f"Usage: {sys.argv[0]} <call stack size> <generation path>"

call_stack_size = int(sys.argv[1])
generation_path = Path(sys.argv[2])


env = Environment(
    loader=FileSystemLoader(Path(__file__).parent.joinpath("templates")),
    autoescape=select_autoescape(),
)
impl_template = env.get_template("impl.cpp.j2")
header_template = env.get_template("functions.h.j2")

generation_path.mkdir(parents=True, exist_ok=True)
with open(generation_path.joinpath("functions.h"), "w") as file:
    file.write(header_template.render(call_stack_size=call_stack_size))

for i in range(call_stack_size):
    with open(generation_path.joinpath(f"impl{i}.cpp"), "w") as file:
        file.write(impl_template.render(call_stack_size=call_stack_size, index=i))
