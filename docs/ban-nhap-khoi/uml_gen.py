"""Sinh UML Class Diagram (draw.io + SVG) cho BankAccountPrj tu mot mo hinh duy nhat.
Ban nhap cua Khoi (18/11). UML chinh thuc la cua Hanh: docs/Nhom_7_UML_Class_Diagram.png
Chay: python3 docs/ban-nhap-khoi/uml_gen.py  -> docs/ban-nhap-khoi/Nhom_7_UML_Class_Diagram.drawio / .svg
"""
import html, os
OUT = os.path.dirname(os.path.abspath(__file__))

CLASSES = {
 "BankAccountManager": dict(attrs=[
    "- accountTypeList: AccountTypeList",
    "- bankAccountList: BankAccountList",
    "- hasUnsavedTypes: bool",
    "- hasUnsavedAccounts: bool"],
  methods=[
    "+ BankAccountManager()",
    "+ run(): int",
    "- loadData(): void",
    "- showMenu(): void",
    "- handleChoice(choice: int): bool",
    "- listAccountTypes() ... saveBankAccounts(): void  [CN 1-11]",
    "- depositMoney() / withdrawMoney() / showYearlyInterest(): void",
    "- confirmExit(): bool  [0 - Exit]"]),
 "Menu": dict(attrs=[], methods=[
    "+ int_getChoice<T>(options: std::vector<T>): int",
    "+ ref_getChoice<T>(options: std::vector<T>): T"]),
 "AccountTypeList": dict(attrs=["- accountTypes: std::vector<AccountType>"], methods=[
    "+ AccountTypeList()",
    "+ loadFromFile(filename: std::string): bool",
    "+ saveToFile(filename: std::string): bool",
    "+ searchID(id: std::string): int",
    "+ findByID(id: std::string): AccountType*",
    "+ getUserChoice(): AccountType",
    "+ addAccountType(type: AccountType): void",
    "+ updateAccountType(id: std::string, updated: AccountType): bool",
    "+ listAccountTypes(): void",
    "+ getAll(): std::vector<AccountType>"]),
 "BankAccountList": dict(attrs=[
    "- bankAccounts: std::vector<BankAccount>",
    "- accountTypeList: const AccountTypeList&"], methods=[
    "+ BankAccountList(types: const AccountTypeList&)",
    "+ loadFromFile(filename: std::string): bool",
    "+ saveToFile(filename: std::string): bool",
    "+ searchID(id: std::string): int",
    "+ findByID(id: std::string): BankAccount*",
    "+ addBankAccount(account: BankAccount): void",
    "+ removeBankAccount(id: std::string): bool",
    "+ updateBankAccount(id: std::string, updated: BankAccount): bool",
    "+ listBankAccounts(): void",
    "+ printBasedAccountTypeName(keyword: std::string): void",
    "+ deposit(id: std::string, amount: double): bool",
    "+ withdraw(id: std::string, amount: double): bool",
    "+ syncAccountType(oldTypeID: std::string, updated: AccountType): void",
    "- sortAccounts(): void"]),
 "AccountType": dict(attrs=[
    "- accountTypeID: std::string",
    "- typeName: std::string",
    "- currency: std::string",
    "- interestRate: double"], methods=[
    "+ AccountType()",
    "+ AccountType(std::string, std::string, std::string, double)",
    "+ getters / setters",
    "+ toString(): std::string"]),
 "BankAccount": dict(attrs=[
    "- accountID: std::string",
    "- accountType: AccountType",
    "- ownerName: std::string",
    "- accountNumber: std::string",
    "- balance: double"], methods=[
    "+ BankAccount()",
    "+ BankAccount(std::string, AccountType, std::string, std::string, double)",
    "+ getters / setters",
    "+ toString(): std::string",
    "+ screenString(): std::string",
    "+ operator<(other: const BankAccount&): bool"]),
}

CH = 7.3      # do rong 1 ky tu (DejaVu Sans Mono 12px)
LH = 17       # chieu cao dong
HEAD = 30     # o ten class
PAD = 10

def size(name):
    c = CLASSES[name]
    lines = c["attrs"] + c["methods"] + [name]
    w = max(len(s) for s in lines) * CH + 2 * PAD
    h = HEAD + (max(len(c["attrs"]), 1) + len(c["methods"])) * LH + 2 * 8 + 6
    return int(w), int(h)

# bo cuc 3 hang: Manager + Menu / 2 List / 2 thuc the
GAP_X, GAP_Y = 120, 90
sz = {n: size(n) for n in CLASSES}
colL = max(sz["AccountTypeList"][0], sz["AccountType"][0])
colR = max(sz["BankAccountList"][0], sz["BankAccount"][0])
X0, Y0 = 40, 40
xL, xR = X0, X0 + colL + GAP_X
row1 = max(sz["BankAccountManager"][1], sz["Menu"][1])
row2 = max(sz["AccountTypeList"][1], sz["BankAccountList"][1])
y1, y2 = Y0 + 40, Y0 + 40 + row1 + GAP_Y
y3 = y2 + row2 + GAP_Y
pos = {
 "BankAccountManager": (xL + (colL + GAP_X + colR - sz["BankAccountManager"][0]) // 2 - 180, y1),
 "AccountTypeList": (xL, y2), "BankAccountList": (xR, y2),
 "AccountType": (xL, y3), "BankAccount": (xR, y3),
}
pos["Menu"] = (pos["BankAccountManager"][0] + sz["BankAccountManager"][0] + 80, y1 + 40)
W = max(p[0] + sz[n][0] for n, p in pos.items()) + 40
H = max(p[1] + sz[n][1] for n, p in pos.items()) + 70

def box(n):
    x, y = pos[n]; w, h = sz[n]; return x, y, w, h

def anchor(n, side, frac=0.5):
    x, y, w, h = box(n)
    return {"top": (x + w * frac, y), "bottom": (x + w * frac, y + h),
            "left": (x, y + h * frac), "right": (x + w, y + h * frac)}[side]

# (nguon, canh nguon, dich, canh dich, kieu, nhan nguon, nhan dich, nhan giua)
mgr_w = sz["BankAccountManager"][0]
EDGES = [
 ("BankAccountManager", "bottom", "AccountTypeList", "top", "composition", "1", "1", "", 0.25, 0.5),
 ("BankAccountManager", "bottom", "BankAccountList", "top", "composition", "1", "1", "", 0.75, 0.3),
 ("BankAccountManager", "right", "Menu", "left", "dependency", "", "", "<<use>>", 0.35, 0.5),
 ("AccountTypeList", "bottom", "AccountType", "top", "composition", "1", "0..*", "quan ly vector", 0.5, 0.5),
 ("BankAccountList", "bottom", "BankAccount", "top", "composition", "1", "0..*", "quan ly vector", 0.5, 0.5),
 ("BankAccountList", "left", "AccountTypeList", "right", "association", "", "1", "tham chieu", 0.25, 0.25),
 ("BankAccount", "left", "AccountType", "right", "association", "0..*", "1", "thuoc loai", 0.3, 0.3),
]

# ---------------- SVG ----------------
def esc(s): return html.escape(s, quote=True)
svg = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}" font-family="DejaVu Sans Mono, Consolas, monospace" font-size="12">',
 '<defs>',
 '<marker id="open" viewBox="0 0 12 12" refX="11" refY="6" markerWidth="12" markerHeight="12" orient="auto-start-reverse"><path d="M1,1 L11,6 L1,11" fill="none" stroke="#333" stroke-width="1.4"/></marker>',
 '<marker id="diamond" viewBox="0 0 20 12" refX="19" refY="6" markerWidth="20" markerHeight="12" orient="auto-start-reverse"><path d="M1,6 L10,1 L19,6 L10,11 Z" fill="#333"/></marker>',
 '</defs>', f'<rect width="{W}" height="{H}" fill="#ffffff"/>',
 f'<text x="{W/2}" y="32" text-anchor="middle" font-size="18" font-weight="bold" font-family="DejaVu Sans, Arial">BankAccountPrj - UML Class Diagram (Nhom 7, Topic 09)</text>']
for n in CLASSES:
    x, y, w, h = box(n); c = CLASSES[n]
    svg.append(f'<rect x="{x}" y="{y}" width="{w}" height="{h}" fill="#fdfdf6" stroke="#333" stroke-width="1.4"/>')
    svg.append(f'<rect x="{x}" y="{y}" width="{w}" height="{HEAD}" fill="#dae8fc" stroke="#333" stroke-width="1.4"/>')
    svg.append(f'<text x="{x+w/2}" y="{y+20}" text-anchor="middle" font-weight="bold" font-size="13">{esc(n)}</text>')
    yy = y + HEAD + 8
    for a in c["attrs"]:
        yy += LH; svg.append(f'<text x="{x+PAD}" y="{yy-4}">{esc(a)}</text>')
    if not c["attrs"]: yy += LH
    svg.append(f'<line x1="{x}" y1="{yy+4}" x2="{x+w}" y2="{yy+4}" stroke="#333"/>'); yy += 8
    for m in c["methods"]:
        yy += LH; svg.append(f'<text x="{x+PAD}" y="{yy-4}">{esc(m)}</text>')
for s, ss, t, ts, kind, ls, lt, lm, fs, ft in EDGES:
    (x1, y1_), (x2, y2_) = anchor(s, ss, fs), anchor(t, ts, ft)
    sx, sy, sw, sh = box(s); tx, ty, tw, th = box(t)
    if ss in ("bottom", "top"):
        lo, hi = max(sx, tx) + 20, min(sx + sw, tx + tw) - 20
        if lo < hi: x1 = x2 = (lo + hi) / 2 if not (lo <= x1 <= hi) else x1
    else:
        lo, hi = max(sy, ty) + 15, min(sy + sh, ty + th) - 15
        if lo < hi: y1_ = y2_ = (lo + hi) / 2
    if ss in ("bottom", "top"):
        my = (y1_ + y2_) / 2; d = f"M{x1},{y1_} L{x1},{my} L{x2},{my} L{x2},{y2_}"; mid = ((x1 + x2) / 2, my - 6)
    else:
        mx = (x1 + x2) / 2; d = f"M{x1},{y1_} L{mx},{y1_} L{mx},{y2_} L{x2},{y2_}"; mid = (mx, (y1_ + y2_) / 2 + 16)
    attr = 'fill="none" stroke="#333" stroke-width="1.3"'
    if kind == "composition": attr += ' marker-start="url(#diamond)"'
    if kind in ("association", "dependency"): attr += ' marker-end="url(#open)"'
    if kind == "dependency": attr += ' stroke-dasharray="6,4"'
    svg.append(f'<path d="{d}" {attr}/>')
    def lab(px, py, txt, side):
        dx = 10 if side in ("bottom", "top") else (-16 if side == "left" else 16)
        dy = (18 if side == "bottom" else -10) if side in ("bottom", "top") else -10
        anchor_ = "end" if side == "left" else "start"
        svg.append(f'<text x="{px+dx}" y="{py+dy}" text-anchor="{anchor_}" font-size="11" fill="#a40000">{esc(txt)}</text>')
    if ls: lab(x1, y1_, ls, ss)
    if lt: lab(x2, y2_, lt, ts)
    if lm: svg.append(f'<text x="{mid[0]}" y="{mid[1]}" text-anchor="middle" font-size="11" font-style="italic" fill="#555">{esc(lm)}</text>')
legend_y = H - 22
svg.append(f'<text x="40" y="{legend_y}" font-size="11" fill="#555" font-family="DejaVu Sans, Arial">- private  + public  |  hinh thoi den: thanh phan (quan ly vector)  |  mui ten: lien ket (association)  |  net dut: phu thuoc &lt;&lt;use&gt;&gt;  |  main() tao BankAccountManager va goi run()</text>')
svg.append('</svg>')
open(os.path.join(OUT, "Nhom_7_UML_Class_Diagram.svg"), "w").write("\n".join(svg))

# ---------------- draw.io ----------------
cells = []
def label(n):
    c = CLASSES[n]
    a = "<br>".join(esc(x) for x in c["attrs"]) or "&nbsp;"
    m = "<br>".join(esc(x) for x in c["methods"])
    return (f'<p style="margin:0px;margin-top:6px;text-align:center;"><b>{esc(n)}</b></p><hr size="1">'
            f'<p style="margin:0px;margin-left:6px;">{a}</p><hr size="1"><p style="margin:0px;margin-left:6px;">{m}</p>')
ids = {}
for i, n in enumerate(CLASSES, start=2):
    ids[n] = f"c{i}"; x, y, w, h = box(n)
    style = "verticalAlign=top;align=left;overflow=fill;html=1;whiteSpace=wrap;fontFamily=Courier New;fontSize=12;fillColor=#fdfdf6;strokeColor=#333333;"
    cells.append(f'<mxCell id="{ids[n]}" value="{esc(label(n))}" style="{style}" vertex="1" parent="1"><mxGeometry x="{x}" y="{y}" width="{w}" height="{h}" as="geometry"/></mxCell>')
side_xy = {"top": (0.5, 0), "bottom": (0.5, 1), "left": (0, 0.5), "right": (1, 0.5)}
for k, (s, ss, t, ts, kind, ls, lt, lm, fs, ft) in enumerate(EDGES):
    eid = f"e{k}"
    ex, ey = side_xy[ss]; nx, ny = side_xy[ts]
    if ss in ("top", "bottom"): ex = fs
    else: ey = fs
    if ts in ("top", "bottom"): nx = ft
    else: ny = ft
    st = f"edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;exitX={ex};exitY={ey};entryX={nx};entryY={ny};"
    if kind == "composition": st += "startArrow=diamondThin;startFill=1;startSize=14;endArrow=none;"
    elif kind == "association": st += "endArrow=open;endFill=0;endSize=12;"
    else: st += "endArrow=open;endFill=0;dashed=1;endSize=12;"
    cells.append(f'<mxCell id="{eid}" value="{esc(lm)}" style="{st}fontStyle=2;" edge="1" parent="1" source="{ids[s]}" target="{ids[t]}"><mxGeometry relative="1" as="geometry"/></mxCell>')
    for j, (txt, pos_) in enumerate(((ls, -0.85), (lt, 0.85))):
        if txt:
            cells.append(f'<mxCell id="{eid}l{j}" value="{esc(txt)}" style="edgeLabel;html=1;align=center;verticalAlign=middle;fontColor=#A40000;" vertex="1" connectable="0" parent="{eid}"><mxGeometry x="{pos_}" relative="1" as="geometry"><mxPoint as="offset" x="10" y="0"/></mxGeometry></mxCell>')
title = '<mxCell id="t" value="BankAccountPrj - UML Class Diagram (Nhom 7, Topic 09)" style="text;html=1;fontSize=18;fontStyle=1;align=center;" vertex="1" parent="1"><mxGeometry x="0" y="10" width="%d" height="30" as="geometry"/></mxCell>' % W
xml = ('<mxfile host="app.diagrams.net"><diagram name="Class Diagram" id="bams"><mxGraphModel dx="1400" dy="900" grid="1" gridSize="10" page="1" pageWidth="%d" pageHeight="%d"><root><mxCell id="0"/><mxCell id="1" parent="0"/>' % (W, H)
       + title + "".join(cells) + "</root></mxGraphModel></diagram></mxfile>")
open(os.path.join(OUT, "Nhom_7_UML_Class_Diagram.drawio"), "w").write(xml)
print("OK", W, H)
