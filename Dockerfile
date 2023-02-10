FROM docker.io/library/debian:11 AS build

RUN apt-get update \
  && apt-get install -y libsfml-dev build-essential pkg-config

WORKDIR /build

ADD entt ./entt
ADD edyn ./edyn
ADD imgui ./imgui
ADD imgui-sfml ./imgui-sfml
ADD imgui_entt_entity_editor ./imgui_entt_entity_editor

ADD Makefile ./
ADD include ./include
ADD src ./src

RUN make -j"$(nproc)"

FROM docker.io/library/debian:11 AS final

RUN apt-get update \
  && apt-get install -y libsfml-graphics2.5

WORKDIR /app

COPY --from=build /build/spacegame ./
