/* Copyright 2020 the SumatraPDF project authors (see AUTHORS file).
   License: Simplified BSD (see COPYING.BSD) */

#include "BaseUtil.h"

// ------------- Point

Point::Point(int x, int y) : x(x), y(y) {
}

bool Point::empty()  const{
    return x == 0 && y == 0;
}

bool Point::operator==(const Point& other)  const{
    return this->x == other.x && this->y == other.y;
}
bool Point::operator!=(const Point& other)  const{
    return !this->operator==(other);
}

// ------------- PointFl

PointFl::PointFl(float x, float y) : x(x), y(y) {
}

bool PointFl::empty()  const{
    return x == 0 && y == 0;
}

bool PointFl::operator==(const PointFl& other)  const{
    return this->x == other.x && this->y == other.y;
}
bool PointFl::operator!=(const PointFl& other)  const{
    return !this->operator==(other);
}

// ------------- Size

Size::Size(int dx, int dy) : dx(dx), dy(dy) {
}

bool Size::IsEmpty() const {
    return dx == 0 || dy == 0;
}

// TODO: temporary
bool Size::empty() const {
    return dx == 0 || dy == 0;
}

bool Size::operator==(const Size& other) const {
    return this->dx == other.dx && this->dy == other.dy;
}
bool Size::operator!=(const Size& other) const {
    return !this->operator==(other);
}

// ------------- SizeFl

SizeFl::SizeFl(float dx, float dy) : dx(dx), dy(dy) {
}

bool SizeFl::IsEmpty() const {
    return dx == 0 || dy == 0;
}

// TODO: temporary
bool SizeFl::empty() const {
    return dx == 0 || dy == 0;
}

bool SizeFl::operator==(const SizeFl& other) const {
    return this->dx == other.dx && this->dy == other.dy;
}

bool SizeFl::operator!=(const SizeFl& other) const {
    return !this->operator==(other);
}

// ------------- Rect

Rect::Rect(const RECT r) {
    x = r.left;
    y = r.top;
    dx = r.right - r.left;
    dy = r.bottom - r.top;
}

Rect::Rect(const Gdiplus::RectF r) {
    x = (int)r.X;
    y = (int)r.Y;
    dx = (int)r.Width;
    dy = (int)r.Height;
}

Rect::Rect(int x, int y, int dx, int dy) : x(x), y(y), dx(dx), dy(dy) {
}

Rect::Rect(const Point min, const Point max) : x(min.x), y(min.y), dx(max.x - min.x), dy(max.y - min.y) {
}

int Rect::Width() const {
    return dx;
}

int Rect::Height() const {
    return dy;
}

int Rect::Dx() const {
    return dx;
}

int Rect::Dy() const {
    return dy;
}

bool Rect::EqSize(int otherDx, int otherDy) const {
    return (dx == otherDx) && (dy == otherDy);
}

int Rect::Right() const {
    return x + dx;
}

int Rect::Bottom() const {
    return y + dy;
}

Rect Rect::FromXY(int xs, int ys, int xe, int ye) {
    if (xs > xe) {
        std::swap(xs, xe);
    }
    if (ys > ye) {
        std::swap(ys, ye);
    }
    return Rect(xs, ys, xe - xs, ye - ys);
}

Rect Rect::FromXY(Point TL, Point BR) {
    return FromXY(TL.x, TL.y, BR.x, BR.y);
}

bool Rect::IsEmpty() const {
    return dx == 0 || dy == 0;
}
bool Rect::empty() const {
    return dx == 0 || dy == 0;
}

bool Rect::Contains(Point pt) const {
    if (pt.x < this->x) {
        return false;
    }
    if (pt.x > this->x + this->dx) {
        return false;
    }
    if (pt.y < this->y) {
        return false;
    }
    if (pt.y > this->y + this->dy) {
        return false;
    }
    return true;
}

/* Returns an empty rectangle if there's no intersection (see IsEmpty). */
Rect Rect::Intersect(Rect other) const {
    /* The intersection starts with the larger of the start coordinates
        and ends with the smaller of the end coordinates */
    int _x = std::max(this->x, other.x);
    int _y = std::max(this->y, other.y);
    int _dx = std::min(this->x + this->dx, other.x + other.dx) - _x;
    int _dy = std::min(this->y + this->dy, other.y + other.dy) - _y;

    /* return an empty rectangle if the dimensions aren't positive */
    if (_dx <= 0 || _dy <= 0) {
        return {};
    }
    return {_x, _y, _dx, _dy};
}

Rect Rect::Union(Rect other) const {
    if (this->dx <= 0 && this->dy <= 0) {
        return other;
    }
    if (other.dx <= 0 && other.dy <= 0) {
        return *this;
    }

    /* The union starts with the smaller of the start coordinates
        and ends with the larger of the end coordinates */
    int _x = std::min(this->x, other.x);
    int _y = std::min(this->y, other.y);
    int _dx = std::max(this->x + this->dx, other.x + other.dx) - _x;
    int _dy = std::max(this->y + this->dy, other.y + other.dy) - _y;

    return {_x, _y, _dx, _dy};
}

void Rect::Offset(int _x, int _y) {
    x += _x;
    y += _y;
}

void Rect::Inflate(int _x, int _y) {
    x -= _x;
    dx += 2 * _x;
    y -= _y;
    dy += 2 * _y;
}

Point Rect::TL() const {
    return Point(x, y);
}

Point Rect::BR() const {
    return Point(x + dx, y + dy);
}

Size Rect::Size() const {
    return {dx, dy};
}

Rect Rect::FromRECT(const RECT& rect) {
    return FromXY(rect.left, rect.top, rect.right, rect.bottom);
}

bool Rect::operator==(const Rect& other) const {
    return this->x == other.x && this->y == other.y && this->dx == other.dx && this->dy == other.dy;
}
bool Rect::operator!=(const Rect& other) const {
    return !this->operator==(other);
}

// ------------- Rect

// ------------- conversion functions

PointFl ToPointFl(const Point p) {
    return {(float)p.x, (float)p.y};
}

Point ToPoint(const PointFl p) {
    return Point{(int)p.x, (int)p.y};
}

SizeFl ToSizeFl(const Size s) {
    return {(float)s.dx, (float)s.dy};
}

SIZE ToSIZE(const Size s) {
    return {s.dx, s.dy};
}

Size ToSize(const SizeFl s) {
    int dx = (int)floor(s.dx + 0.5);
    int dy = (int)floor(s.dy + 0.5);
    return Size(dx, dy);
}

RectFl ToRectFl(const Rect r) {
    return {(float)r.x, (float)r.y, (float)r.dx, (float)r.dy};
}

RECT ToRECT(const Rect r) {
    return {r.x, r.y, r.x + r.dx, r.y + r.dy};
}

Gdiplus::Rect ToGdipRect(const Rect r) {
    return Gdiplus::Rect(r.x, r.y, r.dx, r.dy);
}

Gdiplus::RectF ToGdipRectF(const Rect r) {
    return Gdiplus::RectF((float)r.x, (float)r.y, (float)r.dx, (float)r.dy);
}

RECT ToRECT(const RectFl r) {
    return {(int)r.x, (int)r.y, (int)(r.x + r.dx), (int)(r.y + r.dy)};
}

Rect ToRect(const RectFl r) {
    int x = (int)floor(r.x + 0.5);
    int y = (int)floor(r.y + 0.5);
    int dx = (int)floor(r.dx + 0.5);
    int dy = (int)floor(r.dy + 0.5);
    return Rect(x, y, dx, dy);
}

Gdiplus::Rect ToGdipRect(const RectFl r) {
    Rect rect = ToRect(r);
    return Gdiplus::Rect(rect.x, rect.y, rect.dx, rect.dy);
}

Gdiplus::RectF ToGdipRectF(const RectFl r) {
    return Gdiplus::RectF(r.x, r.y, r.dx, r.dy);
}