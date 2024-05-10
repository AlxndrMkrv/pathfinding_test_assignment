if "DumperBase" not in globals():
    from dumper import DumperBase, Children, SubItem


def qdump__Cell(d: DumperBase, value: DumperBase.Value):
    col = value.findMemberByName("col")
    row = value.findMemberByName("row")
    id = value.findMemberByName("id")

    if None in [col, row, id]:
        d.putValue("<Cell failed>")
        return

    d.putValue(f"({col.integer()}, {row.integer()})")
    d.putExpandable()
    if d.isExpanded():
        with Children(d):
            d.putSubItem("id", id)
